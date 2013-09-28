#ifndef SF_LIST_H
#define SF_LIST_H


#include <assert.h>
#include <stdlib.h>
#include <inttypes.h>


typedef void (sf_list_destructor_t)(void *);

struct sf_list_node {
    struct sf_list_node    *prev;
    struct sf_list_node    *next;
    char                    elt[];  /* flexible array for element's storage */
};


struct sf_list {
    size_t                  size;   /* element's size in bytes */
    uint32_t                nelts;
    struct sf_list_node     head[];
};


struct sf_list *sf_list_create(size_t size);
void sf_list_destroy(struct sf_list *l, sf_list_destructor_t *destructor);
void *sf_list_push(struct sf_list * l, const void *elt);
void *sf_list_push_front(struct sf_list * l, const void *elt);
void sf_list_pop(struct sf_list * l, void *o_elt);
void sf_list_pop_front(struct sf_list * l, void *o_elt);


#define SF_LIST_BEGIN(l, type, name) do {                       \
    assert(sizeof(type) == (l)->size);                          \
    struct sf_list_node *__sf_list_node__ = (l)->head->next;    \
    for (; __sf_list_node__ != (l)->head;                       \
           __sf_list_node__ = __sf_list_node__->next) {         \
        type *name = (type *) __sf_list_node__->elt

#define SF_LIST_END() } } while(0)

#define SF_LIST_HEAD(l) ((void *) (l)->head->next->elt)

#define SF_LIST_TAIL(l) ((void *) (l)->head->prev->elt)


#endif /* SF_LIST_H */
