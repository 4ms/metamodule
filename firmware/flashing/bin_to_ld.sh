cat $1 | hexdump -v -e '"BYTE (0x" 1/1 "%02X" ") \n"' > $2
