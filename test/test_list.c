#include <stdio.h>
#include <string.h>

#include <sf/list.h>


int main(void) {
    sf_list_t       l;
    sf_list_def_t   def;

    memset(&def, 0, sizeof(def));
    def.size = sizeof(char);

    sf_list_init(&l, &def);

    char ch;

    for (ch = 'a'; ch <= 'z'; ++ch) {
        sf_list_push(&l, &ch);
    }

    sf_list_iter_t iter;

    if (sf_list_begin(&l, &iter)) do {
        char *pch = sf_list_iter_elt(&iter);
        fprintf(stdout, "%c", *pch);
    } while (sf_list_iter_next(&iter));

    fprintf(stdout, "\n");

    sf_list_clear(&l);

    if (sf_list_begin(&l, &iter)) do {
        char *pch = sf_list_iter_elt(&iter);
        fprintf(stdout, "%c", *pch);
    } while (sf_list_iter_next(&iter));


    sf_list_destroy(&l);

    return 0;
}
