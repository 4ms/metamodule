# M33 coprocessor firmware (placeholder)

Separate arm-none-eabi CMake project (the A35 project cannot share a toolchain
with it), added as an ExternalProject once the `copro-m33` baremetal example and
the mdrivlib `target/stm32mp2_cm33` land. Use `../../cmake/arch_mp25xm33.cmake`.

Role (confirmed decision): mirrors the MP1 M4 by default — controls/gate jacks,
filesystem (SD/USB/XSPI), wifi — behind the movable `core_intercom` abstraction,
so the split can be revisited after eval-board measurements. Start by porting
`firmware/src/core_m4/`.
