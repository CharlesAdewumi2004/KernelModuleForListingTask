#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/sched/signal.h>  // For task_struct and process list macros

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Your Name");
MODULE_DESCRIPTION("A Linux Kernel Module to List Running Processes");

// Function to convert task state to a readable string
static const char *get_task_state(long state) {
    switch (state) {
        case TASK_RUNNING: return "RUNNING";
        case TASK_INTERRUPTIBLE: return "SLEEPING";
        case TASK_UNINTERRUPTIBLE: return "BLOCKED";
        case __TASK_STOPPED: return "STOPPED";
        case __TASK_TRACED: return "TRACED";
        case EXIT_DEAD: return "EXIT_DEAD";
        case EXIT_ZOMBIE: return "ZOMBIE";
        default: return "UNKNOWN";
    }
}

// Initialization function (runs when the module is loaded)
static int __init list_processes_init(void) {
    struct task_struct *task;  // Pointer to process information

    printk(KERN_INFO "Loading Process Listing Module...\n");

    // Loop through all processes
    for_each_process(task) {
        printk(KERN_INFO "PID: %d | Process Name: %s | State: %s\n", 
               task->pid, task->comm, get_task_state(task->__state));  // Use task->__state
    }

    return 0;
}

// Cleanup function (runs when the module is removed)
static void __exit list_processes_exit(void) {
    printk(KERN_INFO "Unloading Process Listing Module...\n");
}

module_init(list_processes_init);
module_exit(list_processes_exit);
