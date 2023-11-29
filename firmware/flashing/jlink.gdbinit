target extended-remote localhost:2331
symbol-file build/mp1corea7/medium/main.elf
restore build/main.uimg binary 0xD0000000
set *((unsigned int)0x5C00A118) = 0xD0000000
print "Image loaded. Type `continue` to boot."
