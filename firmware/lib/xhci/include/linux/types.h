#ifndef _LINUX_TYPES_H
#define _LINUX_TYPES_H

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

/* As in Linux (u32 is unsigned int): on 32-bit Arm, uint32_t is unsigned long */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;

typedef signed char s8;
typedef short s16;
typedef int s32;
typedef long long s64;

typedef u8 __u8;
typedef u16 __u16;
typedef u32 __u32;
typedef u64 __u64;

typedef u16 __le16;
typedef u32 __le32;
typedef u64 __le64;

typedef unsigned long phys_addr_t;
typedef unsigned long dma_addr_t;
typedef unsigned long resource_size_t;

typedef unsigned int gfp_t;
typedef long long loff_t;
typedef unsigned int uid_t;
typedef unsigned int gid_t;

#define __force
#define __iomem

#endif /* _LINUX_TYPES_H */
