
#ifdef COMPILETIME
	#include <stdio.h>
	#include <malloc.h>

	void* mymalloc(size_t size){
		void *p = malloc(size);
		printf("malloc(%ld):%p\n", size,p);
		return p;
	}

	void myfree(void *p){
		free(p);
		printf("free:%p\n",p);
	}
#endif

#ifdef LINKTIME
	#include <stdio.h>
	void* __real_malloc(size_t size);
	void __real_free(void* p);

	void* __wrap_malloc(size_t size){
		void *p = __real_malloc(size);
		printf("malloc(%ld):%p\n", size,p);
		return p;
	}

	void __wrap_free(void *p){
		__real_free(p);
		printf("free:%p\n",p);
	}
#endif

#ifdef RUNTIME
	#define _GNU_SOURCE
	#include <stdio.h>
	#include <stdlib.h>
	#include <dlfcn.h>

	void *malloc(size_t size){
	    void *(*mallocp)(size_t size);
	    char *error;
	    // 查找标准库的实现
	    mallocp = dlsym(RTLD_NEXT, "malloc");
	    if ((error = dlerror()) != NULL) {
	        // fputs(error, stderr);
	        fprintf(stderr,"%s\n",error);
	        exit(1);
	    }
	    void *ptr = mallocp(size);
	    fprintf(stderr,"malloc(%ld):%p\n",size,ptr);
	    return ptr;
	}

	void free(void *ptr){
	    void (*freep)(void *ptr);
	    char *error;
	    freep = dlsym(RTLD_NEXT, "free");
	    if ((error = dlerror()) != NULL) {
	        fprintf(stderr,"%s\n",error);
	        exit(1);
	    }
	    fprintf(stderr,"free:%p\n",ptr);
	    freep(ptr);
	}
#endif