#include <string.h>

#include "sf/log.h"
#include "sf/utils.h"


void *sf_alloc(size_t size) {
    void *p;

    p = malloc(size);
    if (p == NULL) {
        sf_log(SF_LOG_ERR, "sf_alloc: failed to allocate %zu bytes.", size);
        abort();
    }

    sf_log(SF_LOG_INFO, "sf_alloc: allocated %zu bytes.", size);

    return p;
}

void *sf_calloc(size_t size) {
    void *p;

    p = sf_alloc(size);
    memset(p, 0, size);

    return p;
}
