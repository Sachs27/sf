#include <stdio.h>
#include <sf/pool.h>


int main(void) {
    sf_pool_t p;

    printf("%p\n", &p);

    sf_pool_init(&p, 0);

    printf("%p\n", sf_pool_alloc(&p, 1));
    printf("%p\n", sf_pool_alloc(&p, 1));
    printf("%p\n", sf_pool_alloc(&p, 100));
    printf("%p\n", sf_pool_alloc(&p, 100));
    printf("%p\n", sf_pool_alloc(&p, 100));
    printf("%p\n", sf_pool_alloc(&p, 100));
    printf("%p\n", sf_pool_alloc(&p, 100));
    printf("%p\n", sf_pool_alloc(&p, 100));
    printf("%p\n", sf_pool_alloc(&p, 100));
    printf("%p\n", sf_pool_alloc(&p, 100));
    printf("%p\n", sf_pool_alloc(&p, 100));

    sf_pool_alloc(&p, 200);
    sf_pool_alloc(&p, 2000);
    sf_pool_alloc(&p, 2000);
    sf_pool_alloc(&p, 2000);
    sf_pool_alloc(&p, 2000);

    sf_pool_alloc(&p, 2000000);
    sf_pool_alloc(&p, 20000);
    sf_pool_alloc(&p, 20000);
    sf_pool_alloc(&p, 20000);
    sf_pool_alloc(&p, 20000);

    sf_pool_clear(&p);

    sf_pool_alloc(&p, 100);

    sf_pool_alloc(&p, 200);

    sf_pool_alloc(&p, 200);

    sf_pool_alloc(&p, 2000);

    sf_pool_alloc(&p, 200);
    sf_pool_alloc(&p, 2000);
    sf_pool_alloc(&p, 2000);
    sf_pool_alloc(&p, 2000);
    sf_pool_alloc(&p, 2000);

    sf_pool_destroy(&p);

    return 0;
}
