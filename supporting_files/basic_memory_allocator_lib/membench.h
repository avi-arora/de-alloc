#ifndef CS61_MEMBENCH_H
#define CS61_MEMBENCH_H

typedef struct memnode {
    void* contents;
} memnode;
typedef struct memnode_arena memnode_arena;

memnode_arena* memnode_arena_new(void);
void memnode_arena_free(memnode_arena* arena);

memnode* memnode_alloc(memnode_arena* arena);
void memnode_free(memnode_arena* arena, memnode* m);

#endif
