#include <string.h>

#include "sf/log.h"
#include "sf/utils.h"


uint32_t sf_power_2(uint32_t n) {
    n |= (n >> 16);
    n |= (n >> 8);
    n |= (n >> 4);
    n |= (n >> 2);
    n |= (n >> 1);
    return n + 1;
}

void *sf_alloc(size_t size) {
    void *p;

    p = malloc(size);
    if (p == NULL) {
        sf_log(SF_LOG_PANIC, "sf_alloc: failed to allocate %zu bytes.", size);
        abort();
    }

    sf_log(SF_LOG_INFO, "sf_alloc: allocated %zu bytes.", size);

    return p;
}

void *sf_calloc(size_t size) {
    void *p;

    p = sf_alloc(size);
    sf_memzero(p, size);

    return p;
}

void *sf_realloc(void *p, size_t size) {
    void *newp;

    newp = realloc(p, size);
    if (newp == NULL) {
        sf_log(SF_LOG_PANIC, "sf_realloc: failed to allocate %zu bytes.", size);
        abort();
    }

    sf_log(SF_LOG_INFO, "sf_realloc: allocated %zu bytes.", size);

    return newp;
}
