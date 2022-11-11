//
// Created by Clement on 08/11/2022.
//

#include <stdio.h>
#include "tablist.c"

int main(int argc, char *argv[]) {
    tlist_t *l = tlist_new();
    for (int i = 1; i < argc - 1; i++) {
        int x = atoi(argv[i]);
        int y = atoi(argv[++i]);
        tlist_add(l, x, y);
    }
    tlist_sort(l);
    tlist_print(l);
    tlist_free(l);
    return 0;
}