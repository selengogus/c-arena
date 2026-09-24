#include <mach/mach.h>
#include <stdio.h>
#include "task_info.h"
#include "base.h"

void print_mem_stats() {
    struct task_basic_info info;
    mach_msg_type_number_t count = TASK_BASIC_INFO_COUNT;
    kern_return_t kr = task_info(mach_task_self(), TASK_BASIC_INFO,
                                   (task_info_t)&info, &count);
    if (kr == KERN_SUCCESS) {
        printf("\nresident_size: %.2f MiB\n", (double)info.resident_size / (MiB(1)));
        printf("virtual_size:  %.2f MiB\n", (double)info.virtual_size / (MiB(1)));
    }
}