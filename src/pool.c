#include <string.h>

#include "sf/utils.h"
#include "sf/pool.h"
#include "sf/log.h"


#define SF_ALIGNMENT sizeof(unsigned long)      /* platform word */

#define SF_ALIGN_PTR(p, a)                                  \
    (uint8_t *) (((uintptr_t) (p) + ((uintptr_t) a - 1))    \
                 & ~((uintptr_t) a - 1))


inline static void sf_pool_node_init(sf_pool_node_t *node, size_t size) {
    node->next = NULL;
    node->last = (uint8_t *) (node + 1);
    node->end  = node->last + size;
}

static void *sf_pool_alloc_large(sf_pool_t *pool, size_t size) {
    void            *m;
    sf_pool_large_t *large;

    m = sf_alloc(size);

    for (large = pool->large; large; large = large->next) {
        if (large->alloc == NULL) {
            large->alloc = m;
            return m;
        }
    }

    large = sf_pool_alloc(pool, sizeof(*large));
    large->alloc = m;
    large->next = pool->large;
    pool->large = large;

    return m;
}

static void *sf_pool_alloc_node(sf_pool_t *pool, size_t size) {
    uint8_t         *m;
    size_t           nsize;
    sf_pool_node_t  *node;

    node = sf_alloc((nsize = sizeof(*node) + pool->max));
    sf_pool_node_init(node, nsize);

    m = SF_ALIGN_PTR(node->last, SF_ALIGNMENT);
    node->last = m + size;

    node->next = pool->first;
    pool->first = node;

    return m;
}


sf_result_t sf_pool_init(sf_pool_t *pool, size_t max) {
    size_t nsize;

    pool->max = max ? max : (SF_POOL_PAGESIZ - sizeof(sf_pool_node_t));
    pool->first = sf_alloc((nsize = sizeof(sf_pool_node_t) + pool->max));
    pool->large = NULL;

    sf_pool_node_init(pool->first, nsize);

    return SF_OK;
}

sf_result_t sf_pool_destroy(sf_pool_t *pool) {
    sf_pool_node_t  *node;
    sf_pool_large_t *large;

    for (large = pool->large; large; large = large->next) {
        if (large->alloc) {
            sf_free(large->alloc);
        }
    }

    node = pool->first;
    while (node) {
        sf_pool_node_t *tmp = node;

        node = node->next;
        sf_free(tmp);
    }
}

void *sf_pool_alloc(sf_pool_t *pool, size_t size) {
    uint8_t         *m;
    sf_pool_node_t  *node;

    if (size > pool->max) {
        return sf_pool_alloc_large(pool, size);
    }

    node = pool->first;
    do {
        m = SF_ALIGN_PTR(node->last, SF_ALIGNMENT);

        if ((size_t) (node->end - m) >= size) {
            node->last = m + size;
            return m;
        }

        node = node->next;
    } while (node);

    return sf_pool_alloc_node(pool, size);
}

void *sf_pool_calloc(sf_pool_t *pool, size_t size) {
    uint8_t *m;

    m = sf_pool_alloc(pool, size);
    memset(m, 0, size);

    return m;
}

sf_result_t sf_pool_free(sf_pool_t *pool, void *p) {
    sf_pool_large_t *large;

    for (large = pool->large; large; large = large->next) {
        if (large->alloc == p) {
            sf_free(large->alloc);
            large->alloc = NULL;
            return SF_OK;
        }
    }

    sf_log(SF_LOG_WARN, "sf_pool_free: %p isn't a large pointer.", p);

    return SF_INVAL;
}

void sf_pool_clear(sf_pool_t *pool) {
    sf_pool_node_t  *node;
    sf_pool_large_t *large;

    for (large = pool->large; large; large = large->next) {
        if (large->alloc) {
            sf_free(large->alloc);
        }
    }

    pool->large = NULL;

    for (node = pool->first; node; node = node->next) {
        node->last = (uint8_t *) (node + 1);
    }
}
