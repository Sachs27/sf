#ifndef SF_LIST_H
#define SF_LIST_H


#include "defs.h"
#include "pool.h"


#ifdef __cplusplus
extern "C" {
#endif


/**
 * # Double-linked list
 *
 * ## Define an integer list
 *
 * ```
 * sf_list_t        l;
 * sf_list_def_t    def;
 *
 * def.size = sizeof(int);
 * def.cmp  = NULL;
 * def.cpy  = NULL;
 * def.free = NULL;
 *
 * sf_list_init(&l, &def);
 * ```
 *
 * ## Iterating the list
 *
 * ```
 * sf_list_iter_t iter;
 *
 * if (sf_list_begin(&l, &iter)) do {
 *     void *elt = sf_list_iter_elt(&iter);
 *
 *     ...
 *
 * } while (sf_list_iter_next(&iter));
 * ```
 */

typedef struct sf_list_def sf_list_def_t;
struct sf_list_def {
    /* size of an element in byte */
    size_t  size;

    /*
     * Function to compare to elements.
     *
     * a and b are the address the each element.
     *
     * If NULL, memcmp is used.
     */
    int (*cmp)(const void *a, const void *b);

    /*
     * Function to copy an element.
     *
     * This is used to populate the element.
     *
     * If NULL, memcpy is used.
     */
    void (*cpy)(void *dst, const void *src);

    /*
     * Function to free an element.
     *
     * Called when deleting an element.
     *
     * If NULL, nothing happened.
     */
    void (*free)(void *elt);
};

typedef struct sf_list_node sf_list_node_t;
struct sf_list_node {
    sf_list_node_t *prev;
    sf_list_node_t *next;
    /*
     * flexible array for allocated memory
     */
};

typedef struct sf_list sf_list_t;
struct sf_list {
    sf_list_node_t  head;
    uint32_t        nelts;
    sf_list_def_t   def;
    sf_pool_t       pool;
};

sf_result_t sf_list_init(sf_list_t *l, const sf_list_def_t *def);

void sf_list_clear(sf_list_t *l);

sf_result_t sf_list_destory(sf_list_t *l);

void *sf_list_push(sf_list_t *l, const void *elt);

void *sf_list_push_front(sf_list_t *l, const void *elt);

sf_result_t sf_list_pop(sf_list_t *l);

sf_result_t sf_list_pop_front(sf_list_t *l);


typedef struct sf_list_iter sf_list_iter_t;
struct sf_list_iter {
    sf_list_t      *l;
    sf_list_node_t *cur;
};


/**
 * Get the first iterator of list.
 *
 * Return SF_FALSE if there is no element in the list.
 */
sf_bool_t sf_list_begin(sf_list_t *l, sf_list_iter_t *iter);

/**
 * Walk to the next element in a list.
 *
 * Return SF_FALSE if there are no more elements to iterate.
 */
sf_bool_t sf_list_iter_next(sf_list_iter_t *iter);

void sf_list_end(sf_list_t *l, sf_list_iter_t *iter);

void *sf_list_insert(sf_list_t *l, sf_list_iter_t *iter, const void *elt);

/**
 * Remove the specity element from a list.
 *
 * The iter will point to the previous element of removed element.
 */
sf_result_t sf_list_remove(sf_list_t *l, sf_list_iter_t *iter);

#define sf_list_iter_elt(iter) ((void *) ((iter)->cur + 1))


#ifdef __cplusplus
}
#endif

#endif /* SF_LIST_H */
