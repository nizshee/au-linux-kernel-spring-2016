#include "stack.h"
#include <linux/list.h>
#include <linux/slab.h>
#include <linux/gfp.h>

stack_entry_t* create_stack_entry(void *data)
{
    stack_entry_t* entry = kmalloc(sizeof(stack_entry_t), GFP_KERNEL);
    entry->data = data;
    INIT_LIST_HEAD(&entry->lh);
    return entry;
}

void delete_stack_entry(stack_entry_t *entry)
{
    list_del(&entry->lh);
    kfree(entry);
}

void stack_push(struct list_head *stack, stack_entry_t *entry)
{
    list_add(&entry->lh, stack);
}

stack_entry_t* stack_pop(struct list_head *stack)
{
    struct list_head* entry = stack->next;
    list_del_init(entry);
    return list_entry(entry, stack_entry_t, lh);;
}
