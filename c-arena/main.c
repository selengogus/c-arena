#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>
#include "task_info.h"
#include "arena.h"

void log_stats(int iter, arena_mem_t* arena) {
    printf("\n[%d] pos=%.1f MiB commit_pos=%.1f MiB", iter,
           (double)arena->pos / (MiB(1)), (double)arena->commit_pos / (MiB(1)));
    print_mem_stats();
}

int main(void) {
    arena_mem_t* arena = create_arena(GiB(1), MiB(1));
    for (int i = 0; i < 64; i++) {
        void* p = push_arena(arena, MiB(16), false);

        if (p == NULL) {
            printf("\n[%d] arena exhausted, stopping \n", i);
            break;
        }

        assert(arena->commit_pos % arena->commit_size == 0);
        assert(arena->commit_pos <= arena->reserve_size);
        memset(p, 0xAB, MiB(16));
        log_stats(i, arena);
    }
    destroy_arena(arena);
}