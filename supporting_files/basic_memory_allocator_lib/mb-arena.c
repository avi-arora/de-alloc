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
    //some way to keep track of free memnodes.
    memnode *freelist; // organised as a internal linked list
};

/*
 * This function should initialize the data structures that you need
 * to represent the arena, initializing all necessary fields.
 */
memnode_arena* memnode_arena_new(void) {
    //  -- Allocate and initialize whatever structures need
    // to create an empty arena.
    memnode_arena *arena = (memnode_arena *) malloc(sizeof(memnode_arena));
    if(arena != NULL)
    {
        arena->groups = NULL;
        arena->freelist = NULL;
        return arena;
    }
    return NULL; //if memory not allocated.
}

void memnode_arena_free(memnode_arena* arena) {
     //Clean up your arena, being sure to free any space you allocated
    // free memory allocated for arena only, this does not free
   // the memory allocated within memnode_group 
   free(arena);  
}

memnode* memnode_alloc(memnode_arena* arena) {
    if(!arena->freelist)
    {
        // No free nodes, must allocate another group!
        // Use `malloc` to allocate the group. Then add all of the
        // group's memnodes to the free_list.
        memnode_group *group = (memnode_group *) malloc(sizeof(memnode_group));
        if(group == NULL)
        {
            return NULL;
        }
        arena->freelist = group->nodes; //add newly allocated space to the free list
    }
    //add an element from the freelist, to fulfill the allocation request
    memnode *node = arena->freelist;
    arena->freelist = (memnode *) node->contents;
    return node;
}

void memnode_free(memnode_arena* arena, memnode* m) {
    // -- And here is the place where you have to free stuff!
    m->contents = arena->freelist;
    arena->freelist = m; 
}
