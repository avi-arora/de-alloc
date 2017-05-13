#include "membench.h"
#include <stdlib.h>

#define MEMNODE_GROUPSIZE 4095

/*
 * The term arena is used to describe the memory that an allocator uses.
 * You will define an arena composed of a variable number of memnode
 * groups, where each memnode group is able to hold MEMNODE_GROUPSIZE
 * memnodes.
 *
 * We define these structures here.
 */

typedef struct memnode_group {
    struct memnode_group* next;
    memnode nodes[MEMNODE_GROUPSIZE];
} memnode_group;

struct memnode_arena {
    memnode_group* groups;
    memnode *free_list;
};

// Idea: All free memnodes in the arena are linked together by
// their `contents`, which is a void*.

memnode_arena* memnode_arena_new(void) {
    memnode_arena* a = (memnode_arena*) malloc(sizeof(memnode_arena));
    a->groups = NULL;
    a->free_list = NULL;
    return a;
}

void memnode_arena_free(memnode_arena* arena) {
    free(arena);
}

memnode* memnode_alloc(memnode_arena* arena) {
    if (!arena->free_list) {
        // No free nodes, must allocate another group!
        // Use `malloc` to allocate the group. Then add all of the
        // group's memnodes to the free_list.
        
    }

    // Pop an element off the free list
    memnode* m = arena->free_list;
    arena->free_list = (memnode*) m->contents;
    return m;
}

void memnode_free(memnode_arena* arena, memnode* m) {
    // Push `m` onto the free list
    m->contents = arena->free_list;
    arena->free_list = m;
}
