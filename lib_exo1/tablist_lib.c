#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

#define ASSERT_NON_EMPTY(l) assert(l->size > 0)

// Exercice 1

// Q1
typedef struct {
    int x;
    int y;
    bool is_in_list; // Remplace is_free qui n'est vraiment pas explicite
    int next;
    int prev;
} elem_t;

// Q2
#define MAX_CAP 100

// Q3
typedef struct {
    int size;
    int first;
    int last;
    elem_t tab[MAX_CAP];
} tlist_t;

//Q4
tlist_t *tlist_new() {
    tlist_t *list = (tlist_t *) malloc(sizeof(tlist_t));
    list->size = 0;
    for (int i = 0; i < MAX_CAP; i++) {
        list->tab[i].is_in_list = false;
        // .is_in_list est false car les cellules ne sont pas dans la liste
    }
    return list;
}

// Q5
int tlist_free(tlist_t *l) {
    free(l);
    return sizeof(tlist_t);
}

// Q6
int tlist_size(tlist_t *l) {
    return l->size;
}

// Utilities
elem_t *get_hd(tlist_t *l) {
    ASSERT_NON_EMPTY(l);
    return &l->tab[l->first];
}

elem_t *get_last(tlist_t *l) {
    ASSERT_NON_EMPTY(l);
    return &l->tab[l->last];
}

//Q7
int tlist_add(tlist_t *l, int x, int y) {
    if (l->size == MAX_CAP) {
        return 0;
    }
    // Search for a free cell
    for (int i = 0; i < MAX_CAP; i++) {
        if (!(l->tab[i].is_in_list)) {
            elem_t *new_elem = &(l->tab[i]);
            if (l->size == 0) {
                l->first = i;
                new_elem->prev = -1;
                assert(i == 0);
            } else {
                l->tab[l->last].next = i;
                new_elem->prev = l->last;
            }
            new_elem->next = -1; // No following elements
            new_elem->x = x;
            new_elem->y = y;
            new_elem->is_in_list = true;
            l->last = i;
            l->size++;

            return 1;
        }
    }
    assert(false); // Unreachable because there is at least one free cell
    return 0;
}

//Q8
int tlist_remove(tlist_t *l, int x, int y) {
    if (l->size == 0) {
        return 0;
    }
    int current_i = l->first;
    while (current_i != -1) {
        elem_t *current = &l->tab[current_i];
        if (current->x == x && current->y == y) {
            if (current->prev == -1) {
                // We are removing the head
                l->first = current->next;
                l->tab[current->next].prev = -1;
            } else {
                l->tab[current->prev].next = current->next;
                if (current->next == -1) {
                    // We are removing the last element
                    l->last = current->prev;
                } else {
                    l->tab[current->next].prev = current->prev;
                }
            }
            current->is_in_list = false;
            l->size--;
            return 1;
        }
        current_i = current->next;
    }
    return 0;
}

//Q9
int tlist_pop(tlist_t *l) {
    if (l->size == 0) {
        return 0;
    }
    elem_t *hd = get_hd(l);
    hd->is_in_list = false;
    l->first = hd->next;
    l->size--;
    return 1;
}

//Q10
int tlist_top(tlist_t *l, int *x, int *y) {
    if (l->size == 0) {
        return 0;
    }
    *x = get_hd(l)->x;
    *y = get_hd(l)->y;
    return 1;
}

//Q11
int tlist_push(tlist_t *l, int x, int y) {
    if (l->size == MAX_CAP) {
        return 0;
    }
    tlist_add(l, x, y);
    elem_t *added = get_last(l);
    int iAdded = l->last;
    if (l->size > 1) {
        l->last = added->prev;
    }
    added->prev = -1;
    added->next = l->first;
    l->first = iAdded;
    get_hd(l)->prev = iAdded;
    return 1;
}

elem_t *tlist_nth(tlist_t *l, int i) {
    if (l->size <= i) {
        return NULL;
    }
    int el = l->first;
    for (int j = 0; j < i; j++) {
        el = l->tab[el].next;
    }
    return &(l->tab[el]);
}

void swap_values(elem_t *elem_i, elem_t *elem_j) {
    // In place
    elem_j->x += elem_i->x;
    elem_i->x = elem_j->x - elem_i->x;
    elem_j->x -= elem_i->x;
    elem_j->y += elem_i->y;
    elem_i->y = elem_j->y - elem_i->y;
    elem_j->y -= elem_i->y;
}

//Q12
int tlist_swap(tlist_t *l, int i, int j) {
    if (l->size <= i || l->size <= j) {
        return 0;
    }
    // On pourrait le faire en une seule passe mais le code est plus lisible comme ça
    elem_t *elem_i = tlist_nth(l, i);
    elem_t *elem_j = tlist_nth(l, j);
    swap_values(elem_i, elem_j);
    return 1;
}

int dist(elem_t *e) {
    int x = e->x;
    int y = e->y;
    return x * x + y * y;
}

//Q13
int tlist_sort(tlist_t *l) {
    if (l->size <= 1) {
        return 1;
    }
    elem_t *to_insert = &l->tab[get_hd(l)->next];
    for (int i = 1; i < l->size; i++) {
        // Invariant : l[0:i] est trié
        elem_t *to_descend = to_insert;
        for (int j = i - 1; j >= 0; j--) {
            elem_t *prev = &(l->tab[to_descend->prev]);
            if (dist(prev) > dist(to_descend)) {
                // swap_values est en place
                swap_values(prev, to_descend);
                to_descend = prev;
            } else {
                break;
            }

        }
        to_insert = &l->tab[to_insert->next];
    }
    return 1;
}

//Q14
int tlist_print(tlist_t *l) {
    if (l->size == 0) {
        return 0;
    }
    elem_t *current = get_hd(l);
    for (int i = 0; i < l->size; i++) {
        printf("(%d, %d) ", current->x, current->y);
        current = &l->tab[current->next];
    }
    return l->size * 2;
}

//Q15
// Dans le fichier `main_exo1.c` à la root du projet