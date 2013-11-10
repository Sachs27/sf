#ifndef SF_POOL_H
#define SF_POOL_H


#include <stdint.h>

#include "defs.h"


#ifdef __cplusplus
extern "C" {
#endif


typedef struct sf_pool_large sf_pool_large_t;
struct sf_pool_large {
    sf_pool_large_t *next;
    void            *alloc;
};

typedef struct sf_pool_node sf_pool_node_t;
struct sf_pool_node {
    sf_pool_node_t *next;
    uint8_t        *last;
    uint8_t        *end;

    /*
     * alloced memory
     */
};

typedef struct sf_pool sf_pool_t;
struct sf_pool {
    sf_pool_node_t     *first;
    size_t              max;
    sf_pool_large_t    *large;
};


sf_result_t sf_pool_init(sf_pool_t *pool);


#ifdef __cplusplus
}
#endif

#endif /* SF_POOL_H */
