#ifndef SF_UTILS_H
#define SF_UTILS_H


#include <inttypes.h>


#define sf_swap(a, b) do {          \
    typeof(a) __sf_swap_tmp__ = a;  \
    a = b;                          \
    b = __sf_swap_tmp__;            \
} while (0)


uint32_t sf_uint_next_power_of_two(uint32_t n);

uint64_t sf_get_ticks(void);


#endif /* SF_UTILS_H */
