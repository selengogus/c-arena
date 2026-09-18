#include <stdio.h>
#include <stdint.h>
#include "platform.h"

int main(void) {
    uint32_t page_size = plat_get_page_size();
    printf("Page size: %u bytes\n", page_size);

    // Reserve
    uint64_t reserve_size = 1024;
    void* reserved_memory = plat_reserve_memory(reserve_size);
    if (reserved_memory == NULL) {
        printf("Failed to reserve memory.\n");
        return 1;
    }
    printf("Reserved %llu bytes of memory at %p\n", reserve_size, reserved_memory);

    // Commit
    if (!plat_commit_memory(reserved_memory, reserve_size)) {
        printf("Failed to commit memory.\n");
        return 1;
    }
    printf("Committed %llu bytes of memory at %p\n", reserve_size, reserved_memory);

    // Decommit
    if (!plat_decommit_memory(reserved_memory, reserve_size)) {
        printf("Failed to decommit memory.\n");
        return 1;
    }
    printf("Decommitted %llu bytes of memory at %p\n", reserve_size, reserved_memory);

    // Release
    if (!plat_release_memory(reserved_memory, reserve_size)) {
        printf("Failed to release memory.\n");
        return 1;
    }
    printf("Released %llu bytes of memory at %p\n", reserve_size, reserved_memory);

    return 0;
}