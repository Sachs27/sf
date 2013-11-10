#ifndef SF_DEFS_H
#define SF_DEFS_H


#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


/** Generic result type
 *
 * - SF_OK  : success
 * - SF_ERR : generic failure
 */
typedef int32_t sf_result_t;
#define SF_ERR -1
#define SF_OK   0

typedef int32_t sf_bool_t;
#define SF_TRUE  1
#define SF_FALSE 0

/**
 * Use this to eliminate 'unused parameter' warnings.
 */
#define sf_unused_param(x) (void) x


#endif /* SF_DEFS_H */
