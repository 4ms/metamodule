#pragma once
#include "ff.h"

// From: http://elm-chan.org/fsw/ff/res/app2.c
// path must point to a buffer large enough to handle longest full path of any entry or sub-entry in the dir

FRESULT delete_node(TCHAR *path,  /* Path name buffer with the sub-directory to delete */
					UINT sz_buff, /* Size of path name buffer (items) */
					FILINFO *fno  /* Name read buffer */
);
