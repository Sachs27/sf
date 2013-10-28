#ifndef DEBUG_H
#define DEBUG_H


#ifdef NDEBUG
# define dprintf(format, ...) ((void) 0)
#else /* NDEBUG */
# include <stdio.h>
# define dprintf(format, ...) fprintf(stdout, format, ##__VA_ARGS__)
#endif /* NDEBUG */


#endif /* DEBUG_H */

