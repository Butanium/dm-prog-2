//
// Created by Clement on 08/11/2022.
//
#include <stdio.h>
#include "holelist.c"
#include <assert.h>

void test_add_remove();

//Q8
int main(int argc, char *argv[]) {
    hlist_t *l = hlist_new();
    for (int i = 1; i < argc; i++) {
        hlist_add(l, atoi(argv[i]));
    }
    hlist_print(l);
    hlist_free(l);
//    test_add_remove(); // Uncomment to run tests
    return 0;
}


void test_add_remove() {
    hlist_t *l = hlist_new();
    for (int i = 0; i < 100; i++) {
        assert(hlist_add(l, i));
    }
    printf("\nTest add passed\n");
    hlist_print(l);
    for (int i = 0; i < 50; i++) {
        assert (hlist_remove(l, i));
    }
    printf("\nTest remove passed\n");
    hlist_print(l);
    for (int i = 0; i < 50; i++) {
        assert (!hlist_remove(l, i));
    }
    printf("\nTest no remove passed\n");
    hlist_print(l);
    fflush(stdout);
    for (int i = 50; i < 100; i++) {
        printf("removing %d\n", i);
        assert (hlist_remove(l, i));
        hlist_print(l);
        printf("\n");
        fflush(stdout);
    }
    printf("\nTest remove2 passed\n");
    hlist_print(l);
    assert(l->height == 1);
    for (int i = 0; i < 100; i++) {
        assert(hlist_add(l, i));
    }
    printf("\nTest add2 passed\n");
    hlist_print(l);
    hlist_free(l);
}
