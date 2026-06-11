target extended-remote localhost:3333
symbol-file build/mp1corea7/medium/main.elf
monitor reset
shell sleep 0.1
restore build/main.uimg binary 0xC0000000
set *((unsigned int)0x5C00A118) = 0xC0000000
print "Image loaded, type `continue` to run"
