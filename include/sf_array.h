#ifndef SF_ARRAY_H
#define SF_ARRAY_H


#include <assert.h>
#include <inttypes.h>


#define SF_ARRAY_NALLOC 4


typedef void (sf_array_destructor_t)(void *);

struct sf_array {
    size_t      size;   /* element's size in bytes */
    void       *elts;
    uint32_t    nelts;
    uint32_t    nalloc;
};


struct sf_array *sf_array_create(size_t size, uint32_t nalloc);
void sf_array_destroy(struct sf_array *a, sf_array_destructor_t *destructor);
void sf_array_clear(struct sf_array *a, sf_array_destructor_t *destructor);
void *sf_array_push(struct sf_array *a, const void *elt);
void sf_array_pop(struct sf_array *a, void *o_elt);


#define SF_ARRAY_NTH(a, n) ((void *) ((char *) (a)->elts + (n) * (a)->size))

#define SF_ARRAY_BEGIN(a, type, name) do {                  \
    assert(sizeof(type) == (a)->size);                      \
    type *name;                                             \
    uint32_t __sf_array_i__ = 0;                            \
    for (; __sf_array_i__ < (a)->nelts; ++__sf_array_i__) { \
        name = SF_ARRAY_NTH(a, __sf_array_i__)

#define SF_ARRAY_END() } } while(0)


#endif /* SF_ARRAY_H */
