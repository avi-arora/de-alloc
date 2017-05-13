membench.c

    A program for benchmarking different malloc implementations.
    We allocate 4096 `memnode` objects, then, NOPERATIONS times
    (which defaults to 10,000,000), free one object and allocate
    another. `memnode` is declared in `membench.h`.

    membench uses an "arena" for its allocations. An arena is an
    object that encapsulates a set of allocations and frees. You
    can use arenas just to capture statistics or to encapsulate
    state for a specialized allocator.

    membench links with different allocator libraries. The simplest
    is mb-malloc.c, which implements the `memnode_alloc()`
    functions with malloc and free. Run this with `./membench-malloc`.
    Run a different number of allocations and/or simultaneous
    threads with `./membench-malloc NOPERATIONS NTHREADS`.
    But it's more interesting to see how much time a run takes.
    For this, use the `time` program:

        time ./membench-malloc

    If your machine has Google's libtcmalloc or Jason Evans's
    libjemalloc, try `./membench-tcmalloc` and `./membench-jemalloc`.
    These allocators should beat the system allocator, especially
    when there is more than one thread.

    membench only allocates fixed-sized objects. Fixed-sized objects
    are much easier to handle than variable-sized objects: they
    reduce fragmentation issues and require less tracking overhead.
    The `mb-arena.c` library is the beginnings of a fixed-size
    allocator that takes advantage of these properties. Can you
    complete it on your own? Run `./membench-arena` to check it.
    Our completed version of `mb-arena.c` beats libtcmalloc and
    libjemalloc by around 6x on my machine!
