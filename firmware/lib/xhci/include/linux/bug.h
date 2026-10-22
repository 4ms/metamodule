#ifndef _LINUX_BUG_H
#define _LINUX_BUG_H

#include <stdio.h>

#define WARN_ON(condition) ({						\
	int __ret_warn_on = !!(condition);				\
	if (unlikely(__ret_warn_on))					\
		printk("WARNING at %s:%d/%s()!\n", __FILE__, __LINE__, __func__); \
	unlikely(__ret_warn_on);					\
})

#define WARN(condition, format...) ({                   \
	int __ret_warn_on = !!(condition);              \
	if (unlikely(__ret_warn_on))                    \
		printf(format);                  \
	unlikely(__ret_warn_on);                    \
})

#define WARN_ON_ONCE(condition)	({				\
	static bool __warned;					\
	int __ret_warn_once = !!(condition);			\
								\
	if (unlikely(__ret_warn_once && !__warned)) {		\
		__warned = true;				\
		WARN_ON(1);					\
	}							\
	unlikely(__ret_warn_once);				\
})

#define WARN_ONCE(condition, format...) ({          \
	static bool __warned;     \
	int __ret_warn_once = !!(condition);            \
								\
	if (unlikely(__ret_warn_once && !__warned)) {       \
		__warned = true;                \
		WARN(1, format);                \
	}                           \
	unlikely(__ret_warn_once);              \
})

/* MetaModule: log, but don't halt (this runs on the core that serves patch storage) */
#define BUG() do { \
	printk("xHCI BUG at %s:%d/%s()!\n", __FILE__, __LINE__, __func__); \
} while (0)

#define BUG_ON(cond) \
	do { \
		if (cond) \
			printf("xHCI BUG_ON at %s:%d\n", __FILE__, __LINE__); \
	} while (0)

#define BUILD_BUG_ON_NOT_POWER_OF_2(n)
#define BUILD_BUG_ON_ZERO(e)	(0)
#define BUILD_BUG_ON(condition)

#endif /* _LINUX_BUG_H */
