#ifndef SF_DEFS_H
#define SF_DEFS_H


#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


/** Generic result type
 *
 * - SF_OK    : success
 * - SF_ERR   : generic failure
 * - SF_NOMEM : out of memory
 * - SF_INVAL : invalid argument
 */
enum sf_result {
    SF_ERR = -1,
    SF_OK = 0,
    SF_NOMEM,
    SF_INVAL,
};
typedef enum sf_result sf_result_t;


enum sf_bool {
    SF_FALSE = 0,
    SF_TRUE = 1,
};
typedef enum sf_bool sf_bool_t;


/**
 * Use this to eliminate 'unused parameter' warnings.
 */
#define sf_unused_param(x) (void) x


#endif /* SF_DEFS_H */
