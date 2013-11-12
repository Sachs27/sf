#include <stdio.h>
#include <string.h>

#include <sf/list.h>
#include <sf/log.h>


int main(void) {
    int n;
    sf_list_t       l;
    sf_list_def_t   def;

    memset(&def, 0, sizeof(def));
    def.size = sizeof(char);

    sf_list_init(&l, &def);

    char ch;

    for (ch = 'a'; ch <= 'z'; ++ch) {
        sf_list_push(&l, &ch);
    }

    while (sf_list_cnt(&l) > 10) {
        fprintf(stdout, "pop: %c\n", * (char *) sf_list_tail(&l));
        sf_list_pop(&l);
    }

    ch = '!';
    sf_list_push_front(&l, &ch);

    while (sf_list_cnt(&l)) {
        fprintf(stdout, "pop: %c\n", * (char *) sf_list_tail(&l));
        sf_list_pop(&l);
    }

    for (ch = 'a'; ch <= 'z'; ++ch) {
        sf_list_push_front(&l, &ch);
    }

    sf_list_iter_t iter;

    if (n = 0, sf_list_begin(&l, &iter)) do {
        char *pch = sf_list_iter_elt(&iter);
        fprintf(stdout, "%c", *pch);
        if (n == 10) {
            ch = '!';
            sf_list_insert(&l, &iter, &ch);
        }
    } while (++n, sf_list_next(&l, &iter));

    fprintf(stdout, "\n");

    for (n = 0; n < sf_list_cnt(&l); ++n) {
        fprintf(stdout, "%dth: %c\n", n, *(char *) sf_list_nth(&l, n));
    }

    sf_list_clear(&l);

    for (ch = 'a'; ch <= 'z'; ++ch) {
        sf_list_push_front(&l, &ch);
    }

    if (n = 0, sf_list_begin_r(&l, &iter)) do {
        char *pch = sf_list_iter_elt(&iter);
        fprintf(stdout, "%c", *pch);
        if (n == 10) {
            break;
        }
    } while (++n, sf_list_next(&l, &iter));

    fprintf(stdout, "\n");
    fprintf(stdout, "cur[10]: %c\n", *(char *) sf_list_iter_elt(&iter));
    fprintf(stdout, "head: %c\n", *(char *) sf_list_head(&l));
    fprintf(stdout, "tail: %c\n", *(char *) sf_list_tail(&l));

    sf_list_remove(&l, &iter);
    fprintf(stdout, "after remove, cur: %c\n",
            *(char *) sf_list_iter_elt(&iter));
    ch = '!';
    sf_list_insert(&l, &iter, &ch);

    do {
        char *pch = sf_list_iter_elt(&iter);
        fprintf(stdout, "%c", *pch);
    } while (sf_list_next(&l, &iter));
    fprintf(stdout, "\n");

    sf_list_destroy(&l);

    return 0;
}
