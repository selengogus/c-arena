#ifndef ARENA_H
#define ARENA_H

#include "types.h"
#include "base.h"

typedef struct {
    uint64_t reserve_size;
    uint64_t commit_size;

    uint64_t commit_pos;
    uint64_t pos;
} arena_mem_t;

#define ARENA_BASE_POS (sizeof(arena_mem_t))
#define ARENA_ALIGN (sizeof(void*))

arena_mem_t* create_arena(uint64_t reserve_size, uint64_t commit_size);
void destroy_arena(arena_mem_t* arena);
void* push_arena(arena_mem_t* arena, uint64_t size, bool32_t non_zero);
void pop_arena(arena_mem_t* arena, uint64_t size);
void pop_arena_to(arena_mem_t* arena, uint64_t pos);
void reset_arena(arena_mem_t* arena);

#define PUSH_STRUCT(arena, type) (type*)push_arena(arena, sizeof(type), false);
#define PUSH_STRUCT_NZ(arena, type) (type*)push_arena(arena, sizeof(type), true);
#define PUSH_ARRAY(arena, type, count) (type*)push_arena(arena, sizeof(type) * (count), false);
#define PUSH_ARRAY_NZ(arena, type, count) (type*)push_arena(arena, sizeof(type) * (count), true);

#endif
