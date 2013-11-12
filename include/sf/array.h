#ifndef SF_ARRAY_H
#define SF_ARRAY_H


#include "defs.h"


#ifdef __cplusplus
extern "C" {
#endif


#define SF_ARRAY_DEF_NALLOC 4

typedef struct sf_array_def sf_array_def_t;
struct sf_array_def {
    /*
     * Hint for the initial element count to allocated,
     *
     * If zero, SF_ARRAY_DEF_NALLOC is used.
     */
    uint32_t    nalloc;

    /* size of an element in byte */
    size_t      size;

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


typedef struct sf_array sf_array_t;
struct sf_array {
    void           *elts;
    uint32_t        nelts;
    uint32_t        nalloc;
    sf_array_def_t  def;
};

sf_result_t sf_array_init(sf_array_t *a, sf_array_def_t *def);

void sf_array_clear(sf_array_t *a);

void sf_array_destroy(sf_array_t *a);

void sf_array_push(sf_array_t *a, const void *elt);

void sf_array_push_front(sf_array_t *a, const void *elt);

void sf_array_pop(sf_array_t *a);

void sf_array_pop_front(sf_array_t *a);


#ifdef __cplusplus
}
#endif

#endif /* SF_ARRAY_H */
