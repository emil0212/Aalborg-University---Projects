#include <stdlib.h>

void * allocate_memory_dynamically(int memory, const void *type){
    return malloc(memory * sizeof type);
}