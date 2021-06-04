target extended-remote localhost:2331
file build/mp1corem4/main.elf
source ../../svd-tools/gdb-svd.py
svd ../../cmsis-svd/data/STMicro/STM32MP157x.svd
