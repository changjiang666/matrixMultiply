#ifndef ALLOC_H_
#define ALLOC_H_
#include <stdlib.h>

#define malloc
#define MALLOC(num, type) (type *) malloc( (num) * sizeof(type) )
void *alloc(size_t size);

#endif // ALLOC_H_
