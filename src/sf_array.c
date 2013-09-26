#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "sf_array.h"
#include "sf_utils.h"
#include "sf_debug.h"


static void increae_capcity(struct sf_array *a) {
    int onalloc = a->nalloc;

    a->nalloc <<= 1;
    a->elts = realloc(a->elts, a->nalloc * a->size);
    assert(a->elts != NULL);
    dprintf("sf_array[%"PRIuPTR"]: increased capcity from %"PRIu32
            " to %"PRIu32".\n",
            (uintptr_t) a, onalloc, a->nalloc);
}

struct sf_array *sf_array_create(size_t size, uint32_t nalloc) {
    struct sf_array *a;

    assert(size > 0 && nalloc > 0);
    nalloc = sf_uint_next_power_of_two(nalloc);
    a = malloc(sizeof(*a));
    assert(a != NULL);
    a->size = size;
    a->elts = malloc(nalloc * size);
    a->nelts = 0;
    a->nalloc = nalloc;

    return a;
}

void sf_array_destroy(struct sf_array *a, sf_array_destructor_t *destructor) {
    sf_array_clear(a, destructor);
    free(a->elts);
    free(a);
}

void sf_array_clear(struct sf_array *a, sf_array_destructor_t *destructor) {
    if (destructor) {
        int i;

        for (i = 0; i < a->nelts; ++i) {
            destructor(SF_ARRAY_NTH(a, i));
        }
    }
    a->nelts = 0;
}

void *sf_array_push(struct sf_array *a, void *elt) {
    void *dst;

    if (elt == NULL) {
        return NULL;
    }

    if (a->nelts == a->nalloc) {
        /* the array is full */
        increae_capcity(a);
    }

    dst = SF_ARRAY_NTH(a, a->nelts);
    memcpy(dst, elt, a->size);
    ++a->nelts;

    return dst;
}
