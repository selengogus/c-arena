#include <stddef.h>
#include "arena.h"
#include "platform.h"
#include "base.h"

arena_mem_t* create_arena(uint64_t reserve_size, uint64_t commit_size) {

    uint32_t page_size = plat_get_page_size();

    reserve_size = ALIGN_UP(reserve_size, page_size);
    commit_size = ALIGN_UP(commit_size, page_size);

    arena_mem_t* arena = plat_reserve_memory(reserve_size);

    if(!plat_commit_memory(arena, commit_size)) {
        return NULL;
    }

    arena->reserve_size = reserve_size;
    arena->commit_size = commit_size;
    arena->commit_pos = commit_size;
    arena->pos = ARENA_BASE_POS;

    return arena;
}

void destroy_arena(arena_mem_t* arena) {
    plat_release_memory(arena, arena->reserve_size);
}

void* push_arena(arena_mem_t* arena, uint64_t size, bool32_t non_zero) {

    uint64_t pos_aligned = ALIGN_UP(arena->pos, ARENA_ALIGN);
    uint64_t new_pos = pos_aligned + size;

    if(new_pos > arena->reserve_size) { return NULL; }

    if(new_pos > arena->commit_pos) {
        uint64_t new_commit_pos = new_pos;
        new_commit_pos += arena->commit_size - 1;
        new_commit_pos -= new_commit_pos % arena->commit_size;
        new_commit_pos = MIN(new_commit_pos, arena->reserve_size);

        uint8_t* mem = (uint8_t*) arena + arena->commit_pos;
        uint64_t commit_size = new_commit_pos - arena->commit_pos;

        if(!plat_commit_memory(mem, commit_size)) { return NULL; }

        arena->commit_pos = new_commit_pos;
    }

    arena->pos = new_pos;

    uint8_t* out = (uint8_t*) arena + pos_aligned;

    if(!non_zero) { memset(out, 0, size); }

    return out;
}

void pop_arena(arena_mem_t* arena, uint64_t size) {
    size = MIN(size, arena->pos - ARENA_BASE_POS);
    arena->pos -= size;
}

void pop_arena_to(arena_mem_t* arena, uint64_t pos) {
    uint64_t size = pos < arena->pos ? arena->pos - pos : 0;
    pop_arena(arena, size);
}

void clear_arena(arena_mem_t* arena) {
    pop_arena_to(arena, ARENA_BASE_POS);
}

