#ifndef _LINUX_ERR_H
#define _LINUX_ERR_H

#define MAX_ERRNO	4095

#define IS_ERR_VALUE(x)	((unsigned long)(x) >= (unsigned long)-MAX_ERRNO)
#define ERR_PTR(err)	((void *)(long)(err))
#define PTR_ERR(ptr)	((long)(ptr))
#define IS_ERR(ptr)	IS_ERR_VALUE((unsigned long)(ptr))

#endif /* _LINUX_ERR_H */
