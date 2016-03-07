#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/sched.h>
#include <linux/slab.h>

#include "stack.h"
#include "assert.h"

static void __init test_stack(void)
{
    LIST_HEAD(data_stack);
    stack_entry_t *tos = NULL;
    const char *tos_data = NULL;
    const char* test_data[] = { "1", "2", "3", "4" };
    long i = 0;

    pr_alert("Testing basic stack\n");

    for (i = 0; i != ARRAY_SIZE(test_data); ++i) {
        stack_push(&data_stack,
            create_stack_entry((void*)test_data[i])
        );
    }

    for (i = ARRAY_SIZE(test_data) - 1; i >= 0; --i) {
        tos = stack_pop(&data_stack);
        tos_data = STACK_ENTRY_DATA(tos, const char*);
        delete_stack_entry(tos);
        printk(KERN_ALERT "%s == %s\n", tos_data, test_data[i]);
        assert(!strcmp(tos_data, test_data[i]));
    }

    assert(stack_empty(&data_stack));
}

static void __init print_processes_backwards(void)
{
    LIST_HEAD(data_stack);
    struct task_struct *task;
    stack_entry_t *tos;
    char* p;
    for_each_process(task) {
        p = kmalloc(1024 * sizeof(char), GFP_KERNEL);
        get_task_comm(p, task);
        stack_push(&data_stack, create_stack_entry((void*)p));
        // printk("%s => %s\n", task->comm, get_task_comm(buffer, task));
    }

    for(; !stack_empty(&data_stack);) {
        tos = stack_pop(&data_stack);
        p = STACK_ENTRY_DATA(tos, char*);
        printk("%s\n", p);
        kfree(p);
        delete_stack_entry(tos);
    }
}

static int __init ll_init(void)
{
    printk(KERN_ALERT "Hello, linked_lists11\n");
    test_stack();
    print_processes_backwards();
    return 0;
}

static void __exit ll_exit(void)
{
    printk(KERN_ALERT "Goodbye, linked_lists!\n");
}

module_init(ll_init);
module_exit(ll_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Linked list exercise module");
MODULE_AUTHOR("Kernel hacker!");
