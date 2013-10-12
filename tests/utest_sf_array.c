#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "sf_array.h"


void free_str(void *elt) {
    char *str = * (char **) elt;

    fprintf(stdout, "Freeing string: %s\n", str);
    free(str);
}

static void utest_sf_array(void) {
    int i;
    char ch;
    char *str;
    struct sf_array *a = sf_array_create(sizeof(char), SF_ARRAY_NALLOC);

    SF_ARRAY_BEGIN(a, char, ptr);
        fprintf(stdout, "%c ", *ptr);
    SF_ARRAY_END();

    fprintf(stdout, "----------------- Begin test -----------------\n");
    fprintf(stdout, "Test sf_array_push:\n");
    for (i = 0; i < SF_ARRAY_NALLOC; ++i) {
        ch = 'a' + i;
        sf_array_push(a, &ch);
        fprintf(stdout, "Pushed '%c'\n", ch);
    }

    ch = *(char *) SF_ARRAY_HEAD(a);
    fprintf(stdout, "\nHead: %c\t", ch);

    ch = *(char *) SF_ARRAY_TAIL(a);
    fprintf(stdout, "Tail: %c\n\n", ch);

    fprintf(stdout, "Echo in normal order:\n");
    SF_ARRAY_BEGIN(a, char, ptr);
        fprintf(stdout, "%c ", *ptr);
    SF_ARRAY_END();
    fprintf(stdout, "\n\n");

    fprintf(stdout, "Clearing array...\n\n");
    sf_array_clear(a, NULL);

    fprintf(stdout, "Test the increasement\n");
    for (i = 0; i < 26; ++i) {
        ch = 'a' + i;
        sf_array_push(a, &ch);
    }
    fprintf(stdout, "Echo in reverse order:\n");
    SF_ARRAY_BEGIN_R(a, char, ptr);
        fprintf(stdout, "%c ", *ptr);
    SF_ARRAY_END();
    fprintf(stdout, "\n\n");

    sf_array_destroy(a, NULL);

    fprintf(stdout, "Test the destructor\n");
    a = sf_array_create(sizeof(char *), SF_ARRAY_NALLOC);
    for (i = 0; i < SF_ARRAY_NALLOC; ++i) {
        str = strdup("I'm a string");
        sf_array_push(a, &str);
    }
    sf_array_destroy(a, free_str);
}



int main(void) {
    utest_sf_array();
    return 0;
}
