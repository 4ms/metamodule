#ifndef _LINUX_LIST_H
#define _LINUX_LIST_H

#include <linux/kernel.h>

struct list_head {
	struct list_head *next, *prev;
};

#define LIST_HEAD_INIT(name)	{ &(name), &(name) }

#define LIST_HEAD(name) \
	struct list_head name = LIST_HEAD_INIT(name)

#define INIT_LIST_HEAD(ptr) \
	do { (ptr)->next = (ptr); (ptr)->prev = (ptr); } while (0)

static inline void list_add_tail(struct list_head *newnode,
				 struct list_head *head)
{
	newnode->next = head;
	newnode->prev = head->prev;
	head->prev->next = newnode;
	head->prev = newnode;
}

static inline void __list_del(struct list_head *prev, struct list_head *next)
{
	next->prev = prev;
	prev->next = next;
}

static inline void list_del(struct list_head *entry)
{
	__list_del(entry->prev, entry->next);
	entry->next = NULL;
	entry->prev = NULL;
}

static inline void list_move_tail(struct list_head *entry,
				  struct list_head *head)
{
	__list_del(entry->prev, entry->next);
	list_add_tail(entry, head);
}

static inline int list_empty(const struct list_head *head)
{
	return head->next == head;
}

#define list_entry(ptr, type, member)	container_of(ptr, type, member)

#define list_for_each_entry(pos, head, member) \
	for (pos = list_entry((head)->next, __typeof__(*pos), member); \
	     &pos->member != (head); \
	     pos = list_entry(pos->member.next, __typeof__(*pos), member))

#define list_first_entry(ptr, type, member) \
	list_entry((ptr)->next, type, member)

#define list_for_each_entry_safe(pos, n, head, member) \
	for (pos = list_entry((head)->next, __typeof__(*pos), member), \
	     n = list_entry(pos->member.next, __typeof__(*pos), member); \
	     &pos->member != (head); \
	     pos = n, n = list_entry(n->member.next, __typeof__(*pos), member))

#endif /* _LINUX_LIST_H */
