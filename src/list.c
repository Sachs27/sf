#include <inttypes.h>
#include <string.h>

#include "sf/log.h"
#include "sf/list.h"


sf_result_t sf_list_init(sf_list_t *l, const sf_list_def_t *def) {
    l->head.prev = l->head.next = &l->head;
    l->nelts = 0;
    memcpy(&l->def, def, sizeof(l->def));
    sf_pool_init(&l->pool, 0);
    return SF_OK;
}

void sf_list_clear(sf_list_t *l) {
    sf_list_iter_t iter;

    if (l->def.free) {
        if (sf_list_begin(l, &iter)) do {
            l->def.free(sf_list_iter_elt(&iter));
        } while (sf_list_next(l, &iter));
    }

    l->head.prev = l->head.next = &l->head;
    l->nelts = 0;

    return sf_pool_clear(&l->pool);
}

void sf_list_destroy(sf_list_t *l) {
    sf_list_iter_t iter;

    if (l->def.free) {
        if (sf_list_begin(l, &iter)) do {
            l->def.free(sf_list_iter_elt(&iter));
        } while (sf_list_next(l, &iter));
    }

    return sf_pool_destroy(&l->pool);
}

void *sf_list_push(sf_list_t *l, const void *elt) {
    sf_list_iter_t iter;

    sf_list_end(l, &iter);

    return sf_list_insert(l, &iter, elt);
}

void *sf_list_push_front(sf_list_t *l, const void *elt) {
    sf_list_iter_t iter;

    sf_list_begin(l, &iter);

    return sf_list_insert(l, &iter, elt);
}

sf_result_t sf_list_pop(sf_list_t *l) {
    sf_list_iter_t iter;

    sf_list_end(l, &iter);
    iter.cur = iter.cur->prev;

    return sf_list_remove(l, &iter);
}

sf_result_t sf_list_pop_front(sf_list_t *l) {
    sf_list_iter_t iter;

    sf_list_begin(l, &iter);

    return sf_list_remove(l, &iter);
}

void *sf_list_head(sf_list_t *l) {
    return l->head.next + 1;
}

void *sf_list_tail(sf_list_t *l) {
    return l->head.prev + 1;
}

void *sf_list_nth(sf_list_t *l, uint32_t nth) {
    int             n;
    sf_list_iter_t  iter;

    if (n = 0, sf_list_begin(l, &iter)) do {
        if (n == nth) {
            return sf_list_iter_elt(&iter);
        }
    } while (++n, sf_list_next(l, &iter));

    sf_log(SF_LOG_ERR, "sf_list_nth: %" PRIu32 " out of range.", nth);
    return NULL;
}

uint32_t sf_list_cnt(sf_list_t *l) {
    return l->nelts;
}


sf_bool_t sf_list_begin(sf_list_t *l, sf_list_iter_t *iter) {
    iter->order = 1;
    iter->cur = l->head.next;
    return iter->cur != &l->head;
}

sf_bool_t sf_list_begin_r(sf_list_t *l, sf_list_iter_t *iter) {
    iter->order = -1;
    iter->cur = l->head.prev;
    return iter->cur != &l->head;
}

sf_bool_t sf_list_next(sf_list_t *l, sf_list_iter_t *iter) {
    if (iter->order > 0) {
        iter->cur = iter->cur->next;
    } else {
        iter->cur = iter->cur->prev;
    }
    return iter->cur != &l->head;
}

void sf_list_end(sf_list_t *l, sf_list_iter_t *iter) {
    iter->cur = &l->head;
}

void *sf_list_insert(sf_list_t *l, sf_list_iter_t *iter, const void *elt) {
    sf_list_node_t *prev = iter->cur->prev;
    sf_list_node_t *next = iter->cur;
    sf_list_node_t *node;
    void           *dst;

    node = sf_pool_alloc(&l->pool, sizeof(*node) + l->def.size);

    prev->next = node;
    node->prev = prev;

    node->next = next;
    next->prev = node;

    dst = node + 1;
    if (l->def.cpy) {
        l->def.cpy(dst, elt);
    } else {
        memcpy(dst, elt, l->def.size);
    }

    ++l->nelts;

    return dst;
}

sf_result_t sf_list_remove(sf_list_t *l, sf_list_iter_t *iter) {
    sf_list_node_t *prev = iter->cur->prev;
    sf_list_node_t *next = iter->cur->next;

    if (iter->cur == &l->head) {
        return SF_INVAL;
    }

    if (l->def.free) {
        l->def.free(sf_list_iter_elt(iter));
    }

#if 0
    sf_pool_node_t *node;
    for (node = l->pool.first; node; node = node->next) {
        if (node->last == (uint8_t *) sf_list_iter_elt(iter) + l->def.size) {
            node->last -= sizeof(sf_list_node_t) + l->def.size;
            sf_log(SF_LOG_DEBUG, "sf_list_remove: clean pool.");
            break;
        }
    }
#endif

    prev->next = next;
    next->prev = prev;

    if (iter->order > 0) {
        iter->cur = prev;
    } else {
        iter->cur = next;
    }

    --l->nelts;

    return SF_OK;
}

void *sf_list_iter_elt(sf_list_iter_t *iter) {
    return iter->cur + 1;
}
