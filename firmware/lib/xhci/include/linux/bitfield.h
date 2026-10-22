#ifndef _LINUX_BITFIELD_H
#define _LINUX_BITFIELD_H

#define FIELD_GET(mask, reg)	(((reg) & (mask)) >> __builtin_ctzl(mask))
#define FIELD_PREP(mask, val)	(((val) << __builtin_ctzl(mask)) & (mask))

#endif /* _LINUX_BITFIELD_H */
