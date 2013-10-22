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


#define SF_ARRAY_NTH(a, n) ({                                               \
    const struct sf_array *__sf_array_nth_a__ = (a);                        \
    uint32_t __sf_array_nth_idx__ = (n);                                    \
    assert(__sf_array_nth_idx__ < __sf_array_nth_a__->nelts);               \
    (void *) ((char *) __sf_array_nth_a__->elts                             \
                       + __sf_array_nth_idx__ * __sf_array_nth_a__->size);  \
})

#define SF_ARRAY_HEAD(a) SF_ARRAY_NTH(a, 0)

#define SF_ARRAY_TAIL(a) SF_ARRAY_NTH(a, (a)->nelts - 1)

#define SF_ARRAY_BEGIN(a, type, name) do {                          \
    const struct sf_array *__sf_array_begin_a__ = (a);              \
    uint32_t __sf_array_begin_idx__ = 0;                            \
    assert(__sf_array_begin_a__->size == sizeof(type));             \
    for (; __sf_array_begin_idx__ < __sf_array_begin_a__->nelts;    \
         ++__sf_array_begin_idx__) {                                \
        type *name = SF_ARRAY_NTH(__sf_array_begin_a__,             \
                                  __sf_array_begin_idx__)

#define SF_ARRAY_END() } } while(0)

#define SF_ARRAY_BEGIN_R(a, type, name) do {                                \
    const struct sf_array *__sf_array_begin_r_a__ = (a);                    \
    uint32_t __sf_array_begin_r_i__ = __sf_array_begin_r_a__->nelts;        \
    assert(__sf_array_begin_r_a__->size == sizeof(type));                   \
    for (; __sf_array_begin_r_i__ > 0; --__sf_array_begin_r_i__) {          \
        type *name = SF_ARRAY_NTH(__sf_array_begin_r_a__,                   \
                                  __sf_array_begin_r_i__ - 1)


#endif /* SF_ARRAY_H */
