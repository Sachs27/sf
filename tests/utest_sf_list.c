#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "sf_list.h"


void free_str(void *elt) {
    char *str = * (char **) elt;

    fprintf(stdout, "Freeing string: %s\n", str);
    free(str);
}

static void utest_sf_list(void) {
    int i;
    char ch;
    char *str;
    struct sf_list *l = sf_list_create(sizeof(char));

    SF_LIST_BEGIN(l, char, ptr);
        fprintf(stdout, "%c ", *ptr);
    SF_LIST_END();
    fprintf(stdout, "----------------- Begin test -----------------\n");
    fprintf(stdout, "Test sf_list_push:\n");
    for (i = 0; i < 26; ++i) {
        ch = 'a' + i;
        sf_list_push(l, &ch);
        fprintf(stdout, "Pushed '%c'\n", ch);
    }

    ch = *(char *) SF_LIST_HEAD(l);
    fprintf(stdout, "\nHead: %c\t", ch);

    ch = *(char *) SF_LIST_TAIL(l);
    fprintf(stdout, "Tail: %c\n\n", ch);

    fprintf(stdout, "Echo in normal order:\n");
    SF_LIST_BEGIN(l, char, ptr);
        fprintf(stdout, "%c ", *ptr);
    SF_LIST_END();
    fprintf(stdout, "\n\n");

    fprintf(stdout, "Echo in reverse order:\n");
    SF_LIST_BEGIN_R(l, char, ptr);
        fprintf(stdout, "%c ", *ptr);
    SF_LIST_END();
    fprintf(stdout, "\n\n");

    sf_list_destroy(l, NULL);

    fprintf(stdout, "Test the destructor\n");
    l = sf_list_create(sizeof(char *));
    for (i = 0; i < 4; ++i) {
        str = strdup("I'm a string");
        sf_list_push(l, &str);
    }
    sf_list_destroy(l, free_str);
}



int main(void) {
    utest_sf_list();
    return 0;
}
