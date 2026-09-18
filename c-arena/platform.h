#ifndef PLATFORM_H
#define PLATFORM_H

#include "types.h"

void* plat_reserve_memory(uint64_t size);
bool32_t plat_commit_memory(void* ptr, uint64_t size);
bool32_t plat_decommit_memory(void* ptr, uint64_t size);
bool32_t plat_release_memory(void* ptr, uint64_t size);

uint32_t plat_get_page_size(void);

#endif