#include <time.h>

#include "sf_utils.h"


uint32_t sf_uint_next_power_of_two(uint32_t n) {
    if (n != 0) {
        --n;
        n |= (n >> 1);
        n |= (n >> 2);
        n |= (n >> 4);
        n |= (n >> 8);
        n |= (n >>16);
        ++n;
    }
    return n;
}

uint64_t sf_get_ticks(void) {
#define SEC2NSEC 1e9
    struct timespec t;

    clock_gettime(CLOCK_REALTIME, &t);

    return t.tv_sec * SEC2NSEC + t.tv_nsec;
}
