_UNUSED0		= 0xC0000000;
_UNUSED0_SZ		= 1M;		/*0x0010'0000*/
_UNUSED0_END	= 0xC0100000;

_TTB			= 0xC0100000;
_TTB_SZ			= 1M;
_TTB_END		= 0xC0200000;

_A7_SYMS		= 0xC1F70000;
_A7_SYMS_SZ		= 256K;		/*0x0004'0000*/ 
_A7_SYMS_END	= 0xC1FB0000;

_M4_RODATA		= 0xC1FB0000;
_M4_RODATA_SZ   = 320K;		/*0x0005'0000*/ 
_M4_RODATA_END	= 0xC2000000;

_A7_CODE		= 0xC2000040;
_A7_CODE_SZ		= 16M - 0x40;/*0x01000000 - 0x40*/
_A7_CODE_END	= 0xC3000000;

_A7_RAM			= 0xC3000000;
_A7_RAM_SZ		= 64M;		/*0x04000000*/
_A7_RAM_END		= 0xC7000000;

_M4_HEAP		= 0xC7000000;
_M4_HEAP_SZ		= 16M;		/*0x00800000*/
_M4_HEAP_END	= 0xC8000000;

_CONSOLEBUF		= 0xC8000000;
_CONSOLEBUF_SZ  = 3M;
_CONSOLEBUF_END	= 0xC8300000;

_VIRTDRIVE		= 0xC8300000;
_VIRTDRIVE_SZ	= 61M;		/*0x03D00000*/
_VIRTDRIVE_END	= 0xCC000000;

_FWBUFFER		= 0xCC000000;
_FWBUFFER_SZ	= 20M;		/*0x01400000*/
_FWBUFFER_END	= 0xCD400000;

_A7_HEAP		= 0xCD400000;
_A7_HEAP_SZ		= 290M;		/*0x12200000*/
_A7_HEAP_END	= 0xDF600000;

_M4_WIFI_BUF     = 0xDF600000;
_M4_WIFI_BUF_SZ  = 8M;       /*0x00800000*/
_M4_WIFI_BUF_END = 0xDFE00000;

_DMABUF			= 0xDFE00000;
_DMABUF_SZ		= 2M;		/*0x00200000*/
_DMABUF_END		= 0xE0000000;

/* SRAM */
_M4_VECT		= 0x00000000; 
_M4_VECT_A7		= 0x38000000; /* Address from A7's perspective*/
_M4_VECT_SZ		= 0x440;
_M4_VECT_END	= 0x10050000;

_M4_CODE		= 0x10000000;	
_M4_CODE_A7		= 0x30000000; /* Address from A7's perspective*/
_M4_CODE_SZ		= 320K;		  /*0x00050000*/
_M4_CODE_END	= 0x10050000;

_M4_STACK		= 0x10050000;
_M4_STACK_SZ	= 64K - 256;
_M4_STACK_END	= 0x1005FF00;

_M4_SHARED_LIST		= 0x1005FF00;
_A7_SHARED_LIST		= 0x3005FF00;
_SHARED_LIST_SZ		= 256;
_M4_SHARED_LIST_END = 0x10060000;
