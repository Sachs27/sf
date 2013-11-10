#ifndef SF_UTILS_H
#define SF_UTILS_H


#include <stddef.h>


/** sf_swap(T, x, y)
 *
 * Swap the content of two variable
 */
#define sf_swap(T, x, y) do {       \
    T __sf_swap_tmp__ = x;          \
    x = y;                          \
    y = __sf_swap_tmp__;            \
} while(0)

/** sf_max(x, y)
 */
#ifdef __GNUC__
#  define sf_max(x, y) ({ \
       typeof(x) __sf_max_x__ = (x);    \
       typeof(y) __sf_max_y__ = (y);    \
       __sf_max_x__ > __sf_max_y__      \
           ? __sf_max_x__               \
           : __sf_max_y__;              \
   })
#else
#  define sf_max(x, y) ((x) > (y) ? (x) : (y))
#endif /* __GNUC__ */

/** sf_min(x, y)
 */
#ifdef __GNUC__
#  define sf_min(x, y) ({ \
       typeof(x) __sf_min_x__ = (x);    \
       typeof(y) __sf_min_y__ = (y);    \
       __sf_min_x__ < __sf_min_y__      \
           ? __sf_min_x__               \
           : __sf_min_y__;              \
   })
#else
#  define sf_min(x, y) ((x) < (y) ? (x) : (y))
#endif /* __GNUC__ */

/** sf_offsetof(type, filed)
 */
#ifdef __GNUC__
#  define sf_offsetof(type, filed) __buildin_offsetof(type, field)
#else
#  define sf_offsetof(type, filed) ((size_t) (&((type *) 0)->filed))
#endif /* __GNUC__ */

/** sf_container_of(ptr, type, filed)
 */
#ifdef __GNUC__
#  define sf_container_of(ptr, type, filed) ({                              \
       const typeof(((type *) 0)->filed) *__sf_container_of_ptr__ = (ptr);  \
       (type *) ((char *) __sf_container_of_ptr__                           \
                 - sf_offsetof(type, filed));                               \
   })
#else
#  define sf_container_of(ptr, type, member) \
       ((type *) ((char *) ptr - sf_offsetof(type, member)))
#endif /* __GNUC__ */

/** Round up to next power of 2 */
static inline uint32_t sf_power_2(uint32_t n) {
    n |= (n >> 16);
    n |= (n >> 8);
    n |= (n >> 4);
    n |= (n >> 2);
    n |= (n >> 1);
    return n + 1;
}


#endif /* SF_UTILS_H */
