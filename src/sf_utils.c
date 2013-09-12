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
