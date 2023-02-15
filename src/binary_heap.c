//
//  binary_heap.c
//  binary_heap
//
//  Created by Fang Ling on 2023/2/14.
//

#include "binary_heap.h"
#include "array.h"

#define var __auto_type

/** Begin: Creating a heap **/
struct BinaryHeap* binary_heap_init(Int element_size,
                                    Int (*compare)(void* lhs, void* rhs)) {
    var heap = (struct BinaryHeap*)malloc(sizeof(struct BinaryHeap));
    heap -> count = 0;
    heap -> is_empty = true;
    heap -> compare = compare;
    heap -> storage = array_init(element_size);

    return heap;
}
/** End: Creaing a heap **/

/** Begin: Destroying a heap **/
void binary_heap_deinit(struct BinaryHeap* heap) {
    array_deinit(heap -> storage);
    free(heap);
}
/** End: Destroying a heap **/

/** Begin: Private helpers **/
/* Index calculation functions */
static inline Int left(Int i)   { return 2 * i + 1; }   /* Left child */
static inline Int right(Int i)  { return 2 * i + 2; }   /* Right child */
static inline Int parent(Int i) { return (i - 1) / 2; } /* Parent */
/** End: Private helpers **/
