#include "membench.h"
#include <stdlib.h>

memnode_arena* memnode_arena_new(void) {
    return NULL;
}

void memnode_arena_free(memnode_arena* arena) {
    (void) arena;
}

memnode* memnode_alloc(memnode_arena* arena) {
    (void) arena;
    return (memnode*) malloc(sizeof(memnode));
}

void memnode_free(memnode_arena* arena, memnode* m) {
    (void) arena;
    free(m);
}
