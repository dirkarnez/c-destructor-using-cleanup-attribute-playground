#define DEFER(type, name, init_func, fini_func_name) \
    type name __attribute__ ((__cleanup__(fini_func_name))) = init_func

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

void* log_malloc(size_t size) {
    void* ptr = malloc(size);
    printf("Allocated %zu bytes: %p\n", size, ptr);
    return ptr;
}

void log_free(char** ptr) {
    free(*ptr);
    printf("Freed %p\n", *ptr);
}

int test() {
    DEFER(char*, a, log_malloc(10), log_free);

    /*

    __cleanup__ is just a compiler-trick to inject finalizer code, 
    the above and the below generate identical assembly code:
    
    char* c = log_malloc(10);
    log_free(&c);
    */

    // DEFER(char*, b, log_malloc(20), log_free);
    // DEFER(char*, c, log_malloc(30), log_free);
    return 0;
}

int main() {
    test();
   return 0;
}
