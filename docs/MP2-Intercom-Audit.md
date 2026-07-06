# Inter-core comm 64-bit audit (MP2 port, Phase 0)

On MP1 both cores are 32-bit ARM (2×A7 + M4): same pointer width, same
endianness, compatible struct layouts — so the HSEM + shared-memory-struct IPC
can freely share pointers and `std::span`s. On MP2 the A35s run AArch64
(64-bit pointers, LP64) while the M33 is 32-bit, so **any pointer,
`std::span`, `size_t`, or `long` in a struct that crosses the core boundary is
a layout mismatch and/or an unusable address**. This audit lists what must
change before the `core_intercom` port. (Decision: the M33 mirrors the M4's
role; the transport abstraction should make the split movable.)

## Findings

### `src/core_intercom/intercore_message.hh` — `IntercoreStorageMessage`

| Field | Problem on A35↔M33 |
|---|---|
| `std::span<char> buffer` | pointer + `size_t`: 8 bytes on 32-bit, 16 on AArch64; raw address crosses cores |
| `PatchDirList *patch_dir_list` | pointer width 4 vs 8 |
| `uint32_t *bytes_processed` | pointer width 4 vs 8 |
| `PluginFileList *plugin_file_list` | pointer width 4 vs 8 |
| `DirTree<FileEntry> *dir_entries` | pointer width 4 vs 8 |
| `std::optional<uint32_t>` | layout not ABI-pinned across arm32/aarch64 (in practice 8 bytes on both, but replace with `uint32_t value + bool valid` or a sentinel to be explicit) |
| `MessageType : uint32_t`, `uint32_t` fields, `StaticString<N>` | OK (fixed width, no padding surprises) — verify `Volume`, `WifiIPResult`, `FlashTarget` enums have pinned underlying types |

### `src/core_intercom/intercore_modulefs_message.hh` — `IntercoreModuleFS::Message`

- `Read`/`GetS`/`Write`/`Append` carry `std::span<char>` / `std::span<const char>`; `GetS` also `char *res`.
- `FIL`/`DIR` (FatFs) embedded by value: FatFs config must be identical on both
  cores AND `FIL` contains internal pointers (`fs`, buffers) — FatFs runs on the
  M33 side only, so these must become opaque 32-bit handles rather than shared
  structs, or the `FIL` stays M33-private and only an index/handle crosses.
- `std::variant<...>` message: variant index + storage layout must match across
  ABIs — replace with a tagged union with explicit `uint32_t` tag, or pin with
  static_asserts on both builds.

### `src/core_intercom/shared_memory.hh` — `SharedMemoryS::Ptrs`

All 8 members are raw pointers, written by one core and read by the other.
For MP2 these must become fixed 32-bit *addresses/offsets* (`uint32_t`) into a
shared region both cores can address (with an agreed base), or the struct is
per-core-populated from link-time constants rather than shared.

### `src/core_a7/static_buffers.hh`

Placement/layout of the shared blocks (param blocks, audio DMA blocks, ramdisk,
console buffers) is address-map dependent; fine as a pattern, but every member
type it places in shared memory inherits the constraints above (audit
`DoubleBufParamBlock`, `RamDrive`, `ConcurrentBuffer` for `size_t`/pointer
members — `ConcurrentBuffer` in particular has a `size_t` write index if it
follows the usual pattern).

## Recommended replacement idioms (for the intercom refactor)

- pointer → `uint32_t` offset into a named shared region (both cores add their
  own view base); wrap in a small `SharedPtr32<T>` type with `.get(base)`.
- `std::span<char>` → `struct { uint32_t offset; uint32_t size; }`.
- `std::optional<uint32_t>` → explicit `uint32_t value; uint32_t valid;`.
- `std::variant` → `uint32_t tag` + union of fixed-layout structs.
- Every struct that crosses the boundary gets
  `static_assert(sizeof(X) == <N>)` **compiled on both cores' builds** (the
  M33 project and the A35 project), so a divergence is a build error, plus
  `std::has_unique_object_representations_v<X>` where feasible (catches hidden
  padding).
- Shared regions stay non-cacheable on the M33 side; on the A35 side either
  map non-cacheable in the MMU tables (as MP1 does with `.noncachable`) or do
  explicit cache maintenance at the HSEM handoff points.

## Status

DONE — the refactor described above has landed:

- `core_intercom/intercore_types.hh`: `InterCorePtr32<T>`, `InterCoreSpan<T>`,
  `InterCoreOptional<T>`, `InterCoreVariant<Ts...>` (std::visit via
  to_variant()/assignment round-trip, or in-place visit()). Host-tested.
- `IntercoreStorageMessage`: fixed-width members, layout pinned at 620 bytes
  (static_assert compiled on CA7, CM4, and host builds). `wifi_ip_result` uses
  the fixed `InterCoreWifiIPResult` (std::expected is not ABI-pinned).
- `IntercoreModuleFS`: FatFs FIL/DIR no longer cross cores. The fs core owns
  them in `FsObjectTable`s (16 files / 8 dirs) addressed by `FsHandle`;
  responses carry `FsFileState{fptr, objsize, err}` which clients cache inside
  their opaque FIL storage (`fs_handle_cache.hh`), so the plugin-facing
  File/Dir layout and local f_tell/f_size/f_eof/f_error reads are unchanged.
  The shared representation is the fixed-layout `IccMessage`
  (`InterCoreVariant`, pinned at 632 bytes); business logic still uses the
  std::variant `Message` + std::visit, converted at the FsProxy /
  ModuleFSMessageHandler boundary.

Note: the fs server is now stateful. If a client core restarts without closing
its files, handles leak until the fs core restarts — the bring-up code should
reset the tables when a client core reboots (TODO, along with making the
table sizes a conf setting if 16/8 proves tight).

Still open: `SharedMemoryS::Ptrs` (raw pointers, populated by the A7 and read
by the M4) and the `static_buffers` placement — convert with the transport
abstraction when the M33 port lands.
