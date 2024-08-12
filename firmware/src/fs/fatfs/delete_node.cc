#include "console/pr_dbg.hh"
#include "ff.h"

// From: http://elm-chan.org/fsw/ff/res/app2.c

/*------------------------------------------------------------/
/ Delete a sub-directory even if it contains any file
/-------------------------------------------------------------/
/ The delete_node() function is for R0.12+.
/ It works regardless of FF_FS_RPATH.
*/

FRESULT delete_node(TCHAR *path,  /* Path name buffer with the sub-directory to delete */
					UINT sz_buff, /* Size of path name buffer (items) */
					FILINFO *fno  /* Name read buffer */
) {
	UINT i = 0;
	UINT j = 0;
	FRESULT fr = FR_INT_ERR;
	DIR dir;

	fr = f_opendir(&dir, path); /* Open the sub-directory to make it empty */
	if (fr != FR_OK)
		return fr;

	for (i = 0; path[i]; i++)
		; /* Get current path length */
	path[i++] = _T('/');

	for (;;) {
		fr = f_readdir(&dir, fno); /* Get a directory item */
		if (fr != FR_OK || !fno->fname[0])
			break; /* End of directory? */
		j = 0;
		do {						/* Make a path name */
			if (i + j >= sz_buff) { /* Buffer over flow? */
				fr = FR_INT_ERR;
				break; /* Fails when buffer overflow */
			}
			path[i + j] = fno->fname[j];
		} while (fno->fname[j++]);
		if (fno->fattrib & AM_DIR) { /* Item is a sub-directory */
			fr = delete_node(path, sz_buff, fno);
		} else { /* Item is a file */
			fr = f_unlink(path);
		}
		if (fr != FR_OK)
			break;
	}

	path[--i] = 0; /* Restore the path name */
	f_closedir(&dir);

	if (fr == FR_OK)
		fr = f_unlink(path); /* Delete the empty sub-directory */
	return fr;
}
