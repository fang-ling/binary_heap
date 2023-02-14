//
//  binary_heap.h
//  binary_heap
//
//  Created by Fang Ling on 2023/2/14.
//

#ifndef binary_heap_h
#define binary_heap_h

#include <stdlib.h>

#include "types.h"
#include "array.h"
#include "util.h"

struct BinaryHeap {
    /* The number of elements in the heap. */
    Int count;
    /* A Boolean value indicating whether or not the heap is empty. */
    Bool is_empty;
    struct Array* storage;

    /* Compare function, like Java */
    Int (*compare)(void* lhs, void* rhs);
};

#endif /* binary_heap_h */
