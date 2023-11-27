target extended-remote localhost:2331
symbol-file build/mp1corea7/medium/main.elf
restore build/main.uimg binary 0xC2000000
jump Reset_Handler
