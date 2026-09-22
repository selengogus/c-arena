#include "platform.h"
#include <stdbool.h>

#if defined(__APPLE__) || defined(__linux__)

#define _DEFAULT_SOURCE

#include <unistd.h>
#include <sys/mman.h>

static inline void* os_remap_none(void* ptr, uint64_t size) {
    return mmap(ptr, size, PROT_NONE, MAP_PRIVATE | MAP_ANONYMOUS | MAP_FIXED, -1, 0);
}

uint32_t plat_get_page_size(void) {
    return (uint32_t)sysconf(_SC_PAGESIZE);
}

void* plat_reserve_memory(uint64_t size) {
    void* ptr = mmap(NULL, size, PROT_NONE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (ptr == MAP_FAILED) {
        return NULL;
    }
    return ptr;
}

bool32_t plat_commit_memory(void* ptr, uint64_t size) {
    if (mprotect(ptr, size, PROT_READ | PROT_WRITE) != 0) {
        return false;
    }
    return true;
}

bool32_t plat_decommit_memory(void* ptr, uint64_t size) {
    if (mprotect(ptr, size, PROT_NONE) != 0) {
        return false;
    }
    int32_t ret;

    #if defined(__APPLE__)
    ret = os_remap_none(ptr, size) != MAP_FAILED ? 0 : -1;
    #elif defined(__linux__)
    ret = madvise(ptr, size, MADV_DONTNEED);
    #endif

    return ret == 0;
}

bool32_t plat_release_memory(void* ptr, uint64_t size) {
    return munmap(ptr, size) == 0;
}

#endif