
#define malloc(size) mymalloc(size)
#define free(p) myfree(p)

extern void* mymalloc(size_t size);
extern void myfree(void *p);