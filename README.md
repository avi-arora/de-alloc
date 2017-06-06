![alt header](/assets/header.png)
Memory allocation/de-allocation takes ample ammout of time, to cure this masters crafted well engineered solutions e.g tcmalloc, jemalloc and alike. As much as i appreciated their efforts, understanding these highly complex memory allocator is a tough job, also they are designed to solve very specific problem hence can not be used as a general purpose allocator. 

De-alloc is a well designed general purpose memory allocation library that uses standard C memory allocation library and implements handlers to add new functionalities like debugging, overwrite detection, current memory statistics etc. it reduces the complexity of a large scale allocator like jemalloc and tcmalloc, it uses simple data structures and minimises the cache miss ratio by half using custom designed cache centric architecture. 

# Features 
- Tracks memory usage
- Catches common programming errors (e.g. use after free, double free etc)
- Detects writing of the end of dynamically allocated memory (e.g. writing 100 bytes in a 90 bytes space)
- Check for memory leaks 
- Report heavy memory hits (coming soon) 
- Provides easy testing framework

# Usage

1. Memory statistics functions
    The current state of the dynamic allocated memory can be printed using the function

    ```c
    void m61_getstatistics(struct m61_statistics *stats);
    void m61_printstatistics(void);
    void m61_printleakreport(void);
    ```
2.  Memory allocation functions
    ```c
        //for simple memory allocation
        void * m61_malloc(size_t sz, const char *file, int line);
        
        //initilization after allocation
        void *m61_calloc(size_t nmemb, size_t sz, const char *file, int line);
        
        //for reallocation
        void *m61_realloc(void *ptr, size_t sz, const char *file, int line);
    ```
3. Free-up dynamic Memory
    ```c
        void m61_free(void *ptr, const char *file, int line);
    ```
    
# Implementation
De-alloc takes advantage of the stdlib in c, it uses the stantard memory allocation functions malloc() and free(). Apart from that it uses other library functions and encapsulate a protection layer within the allocator by maintaining internal structures of meta-data to track objects of different size classes and give the overall usage statistics to the user via it's own interface. 

The figure below shows how the de-alloc allocates a block of memory, and addup the additional overhead to add debugging facility to the already present memory allocator. 
![alt fig1](/assets/figure1.png)
# Credits 
This project is implemented as an assignment of CS61 curriculum of School of Engineering and Applied Sciences at Harvard University, the distribution code and exact project specification can be found at this [link](https://cs61.seas.harvard.edu/wiki/2015/AllocDebug). 

# License 
