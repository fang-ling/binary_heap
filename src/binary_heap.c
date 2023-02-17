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

/* Maintain the max heap property from node i all the way up to root */
static void max_heapify_up(struct BinaryHeap* heap, Int i) {
    if (i == 0) { /* we are at root node now */
        return;
    }
    /* if parent(i).key <= i.key */
    if (heap -> compare(array_get(heap -> storage, parent(i)),
                        array_get(heap -> storage, i)) <= 0) {
        /* Exchange i with parent(i) */
        array_swap_at(heap -> storage, i, parent(i));
        /* Current node is satisfy max heap property, but maybe not its
         * parent. Fix this recursively.
         */
        max_heapify_up(heap, parent(i));
    }
}

/* Maintain the max heap property from node i all the way down to left */
static void max_heapify_down(struct BinaryHeap* heap, Int i) {
    var j = 0ll;
    /* Current i has both left and right children. */
    /* Let j be one of these children, we want to maximize j.key */
    if (left(i) < heap -> count && right(i) < heap -> count) {
        j = heap -> compare(array_get(heap -> storage, left(i)),
                            array_get(heap -> storage, right(i))) > 0
            ? left(i) : right(i);
    } else if (left(i) < heap -> count && right(i) >= heap -> count) {
        /* Node i only has left child. */
        j = left(i);
    } else if (left(i) >= heap -> count && right(i) < heap -> count) {
        /* Node i only has right child. */
        j = right(i);
    } else {
        /* Node i has zero child. i.e. Node i is a leaf node. We are done. */
        return;
    }
    /* If i is smaller than j (i's largest child), we are violate the max
     * heap property. Fix it by swap i.key with j.key and then recur on j.
     */
    if (heap -> compare(array_get(heap -> storage, i),
                        array_get(heap -> storage, j)) <= 0) {
        array_swap_at(heap -> storage, i, j);
        max_heapify_down(heap, j);
    }
}
/** End: Private helpers **/
