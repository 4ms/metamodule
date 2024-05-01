### Some notes about how ElfFile::ElfReloc (elf_reloc.hh) and ElfFile::Relocator (elf_relocator.hh) work.

A shared object in elf format will contain a table of "relocation" entries.

A relocation entry contains an offset value and an info field.
The info field contains a symbol index and a relocation type. 

- The offset value is the relative address to a word in memory where we need to
  write an address. So if the offset value is 0x100, and we loaded the segment
  into 0xD000'8000 then we are ultimately going to write something to address
  0xD000'8100.
  - In ElfFile::Relocator::write(), we call this `reloc_address` 
  - Sometimes this address already contains a non-zero value, which we call the Addend (I think?)

- The info field encodes a symbol index, points to an entry in the symbol
  table. 
  - The symbol table entry contains an index to a string (the symbol name),
    here we call it `rel.symbol_name()`
  - The entry also contains a "value" field, which (usually?) means the
    symbol's "address" relative to segment start. 
    - The symbol value/address field may be 0, which needs to be handled
      differently than if it contains a non-zero value.

- The info field also encodes a relocation type
  - This is an enum which tells us what action to perform. Here we call this
    `rel.reloc_type()`. Common values are R_ARM_GLOB_DAT, R_ARM_RELATIVE, etc.

When we load the elf file, we load it to a particular address in RAM. This is
the `base_address`.

R_ARM_GLOB_DAT and R_ARM_JUMP_SLOT:
These are the same, except we could optionally resolve the JUMP_SLOT entries 
lazily (but we don't).
- If reloc entry refers to a symbol value/address that is 0, then we need to
  look up that symbol name in out host symbols and write the address of the
  host symbol into the reloc_address
- If it's non-zero, then it (probably?) refers to a local symbol. In that case
  we add the base_address to it.

R_ARM_RELATIVE:
These refer to entries in a GOT for certain static global symbols. Like if the 
code takes the address of some variable that's global to the shared object.
That address is not known at link time so we get a R_ARM_RELATIVE reloc entry
to resolve this.
- If the symbol value is 0, add the base_address to the value that's already at
  the reloc_address.
- If the symbol value is non-zero, then I do not know what to do (I do not
  understand the docs for this type!)


R_ARM_ABS32:
- If the symbol value is 0, then it's the same as R_ARM_GLOB_DAT/JUMP_SLOT
- Otherwise, it's a local symbol. This is the same as R_ARM_GLOB_DAT/JUMP_SLOT
  again, except we also add in the value already at the reloc_address. 

-------

ARM ELF Docs:
https://github.com/ARM-software/abi-aa/blob/main/aaelf32/aaelf32.rst 

- S (when used on its own) is the address of the symbol. (Note: other docs call
  this the "Value" of the symbol) 

- A is the addend for the relocation. (other docs say "Value extracted from the
  storage unit being relcated) 

- P is the address of the place being relocated (derived from r_offset).
  - Another doc says: P: Place (address of the storage unit) being relocated.
    It is calculated using the r_offset field of the relocation directive and
    the base address of the section being relocated. 

- B(S) is the addressing origin of the output segment defining the symbol S.
  The origin is not required to be the base address of the segment. This value
  must always be word-aligned.

Regarding R_ARM_GLOB_DAT:
    "Resolves to the address of the specified symbol"

Regarding R_ARM_JUMP_SLOT:
    S + A
    "Resolves to the address of the specified symbol"

Regarding R_ARM_RELATIVE:
    - (S ≠ 0) B(S) resolves to the difference between the address at which the segment defining the symbol S was loaded and the address at which it was linked.
    - (S = 0) B(S) resolves to the difference between the address at which the segment being relocated was loaded and the address at which it was linked.
