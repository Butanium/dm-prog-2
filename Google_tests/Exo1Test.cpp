//
// Created by Clement on 08/11/2022.
//
#include "gtest/gtest.h"
#include "tablist.c"

// This function converts a tlist_t to an array of int*int :
std::tuple<int, int> *tlist_to_array(tlist_t *l) {
    std::tuple<int, int> *res = new std::tuple<int, int>[l->size];
    int j = l->first;
    for (int i = 0; i < l->size; i++) {
        res[i] = std::make_tuple(l->tab[j].x, l->tab[j].y);
        j = l->tab[j].next;
    }
    return res;
}

TEST(Q4New, EmptyList) {
    tlist_t *l = tlist_new();
    ASSERT_EQ(0, tlist_size(l));
    free(l);
}

TEST(Q7Add, test_size) {
    tlist_t *l = tlist_new();
    ASSERT_EQ(l->size, 0);
    ASSERT_EQ(1, tlist_add(l, 1, 1));
    ASSERT_EQ(l->size, 1);
    ASSERT_EQ(1, tlist_add(l, 2, 3));
    ASSERT_EQ(l->size, 2);
    ASSERT_EQ(1, tlist_add(l, 1, 1));
    ASSERT_EQ(l->size, 3);
    free(l);
}

TEST(Q7Add, test_limit) {
    tlist_t *l = tlist_new();
    for (int i = 0; i < MAX_CAP; i++) {
        ASSERT_EQ(1, tlist_add(l, i, i));
    }
    ASSERT_EQ(l->size, MAX_CAP);
    printf("added MAX_CAP points\n");
    ASSERT_EQ(0, tlist_add(l, 1, 1));
    printf("failed to add one more point\n");
    ASSERT_EQ(l->size, MAX_CAP);
    // Check that every element is in the list
    std::tuple<int, int> *res = tlist_to_array(l);
    ASSERT_NE(nullptr, res);
    for (int i = 0; i < MAX_CAP; i++) {
        ASSERT_EQ(i, std::get<0>(res[i]));
        ASSERT_EQ(i, std::get<1>(res[i]));
    }
    free(l);
}

TEST(Q7Add, test_first_last) {
    tlist_t *l = tlist_new();
    for (int i = 0; i < MAX_CAP; i++) {
        ASSERT_EQ(1, tlist_add(l, i, i));
    }
    // Check first and last
    ASSERT_EQ(l->tab[l->first].x, 0);
    ASSERT_EQ(l->tab[l->first].y, 0);
    ASSERT_EQ(l->tab[l->last].x, MAX_CAP - 1);
    ASSERT_EQ(l->tab[l->last].y, MAX_CAP - 1);
    free(l);
}

TEST(Q8Remove, remove_head) {
    tlist_t *l = tlist_new();
    for (int i = 0; i < MAX_CAP; i++) {
        ASSERT_EQ(1, tlist_add(l, i, i));
    }
    ASSERT_EQ(1, tlist_remove(l, 0, 0));
    ASSERT_EQ(l->size, MAX_CAP - 1);
    ASSERT_EQ(l->first, 1);
    ASSERT_EQ(l->tab[l->first].x, 1);
    ASSERT_EQ(l->tab[l->first].y, 1);
    // Check that every element is in the list
    std::tuple<int, int> *res = tlist_to_array(l);
    ASSERT_NE(nullptr, res);
    for (int i = 1; i < MAX_CAP; i++) {
        ASSERT_EQ(i, std::get<0>(res[i - 1]));
        ASSERT_EQ(i, std::get<1>(res[i - 1]));
    }
    free(l);
    free(res);
}


TEST(Q8Remove, remove_tail) {
    tlist_t *l = tlist_new();
    for (int i = 0; i < MAX_CAP; i++) {
        ASSERT_EQ(1, tlist_add(l, i, i));
    }
    ASSERT_EQ(1, tlist_remove(l, MAX_CAP - 1, MAX_CAP - 1));
    ASSERT_EQ(l->size, MAX_CAP - 1);
    ASSERT_EQ(l->last, MAX_CAP - 2);
    ASSERT_EQ(l->tab[l->last].x, MAX_CAP - 2);
    ASSERT_EQ(l->tab[l->last].y, MAX_CAP - 2);
    // Check that every element is in the list
    std::tuple<int, int> *res = tlist_to_array(l);
    ASSERT_NE(nullptr, res);
    for (int i = 0; i < MAX_CAP - 1; i++) {
        ASSERT_EQ(i, std::get<0>(res[i]));
        ASSERT_EQ(i, std::get<1>(res[i]));
    }
    free(l);
    free(res);
}

TEST(Q8Remove, remove_middle) {
    tlist_t *l = tlist_new();
    for (int i = 0; i < MAX_CAP; i++) {
        ASSERT_EQ(1, tlist_add(l, i, i));
    }
    ASSERT_EQ(1, tlist_remove(l, 10, 10));
    ASSERT_EQ(l->size, MAX_CAP - 1);
    // Check every element in the list
    std::tuple<int, int> *res = tlist_to_array(l);
    ASSERT_NE(nullptr, res);
    for (int i = 0; i < 10; i++) {
        ASSERT_EQ(i, std::get<0>(res[i]));
        ASSERT_EQ(i, std::get<1>(res[i]));
    }
    for (int i = 10; i < MAX_CAP - 1; i++) {
        ASSERT_EQ(i + 1, std::get<0>(res[i]));
        ASSERT_EQ(i + 1, std::get<1>(res[i]));
    }
    free(l);
    free(res);
}

TEST(Q8Remove, remove_nonexistent) {
    tlist_t *l = tlist_new();
    for (int i = 0; i < MAX_CAP; i++) {
        ASSERT_EQ(1, tlist_add(l, i, i));
    }
    ASSERT_EQ(0, tlist_remove(l, 10, 11));
    ASSERT_EQ(l->size, MAX_CAP);
    // Check every element in the list
    std::tuple<int, int> *res = tlist_to_array(l);
    ASSERT_NE(nullptr, res);
    for (int i = 0; i < MAX_CAP; i++) {
        ASSERT_EQ(i, std::get<0>(res[i]));
        ASSERT_EQ(i, std::get<1>(res[i]));
    }
    free(l);
    free(res);
}

TEST(Q8Remove, remove_empty) {
    tlist_t *l = tlist_new();
    ASSERT_EQ(0, tlist_remove(l, 10, 11));
    ASSERT_EQ(l->size, 0);
    free(l);
}

TEST(Q9Pop, empty) {
    tlist_t *l = tlist_new();
    ASSERT_EQ(0, tlist_pop(l));
    ASSERT_EQ(l->size, 0);
    free(l);
}

TEST(Q9Pop, one) {
    tlist_t *l = tlist_new();
    ASSERT_EQ(1, tlist_add(l, 0, 0));
    ASSERT_EQ(1, tlist_pop(l));
    ASSERT_EQ(l->size, 0);
    free(l);
}

TEST(Q9Pop, many) {
    tlist_t *l = tlist_new();
    for (int i = 0; i < MAX_CAP; i++) {
        ASSERT_EQ(1, tlist_add(l, i, i));
    }
    for (int i = 0; i < 10; i++) {
        ASSERT_EQ(1, tlist_pop(l));
    }
    ASSERT_EQ(l->size, MAX_CAP - 10);
    // Check every element in the list
    std::tuple<int, int> *res = tlist_to_array(l);
    ASSERT_NE(nullptr, res);
    for (int i = 0; i < MAX_CAP - 10; i++) {
        ASSERT_EQ(i + 10, std::get<0>(res[i]));
        ASSERT_EQ(i + 10, std::get<1>(res[i]));
    }
    free(l);
}

TEST(Q10Top, empty) {
    tlist_t *l = tlist_new();
    int x, y;
    ASSERT_EQ(0, tlist_top(l, &x, &y));
    ASSERT_EQ(l->size, 0);
    free(l);
}

TEST(Q10Top, two_in_a_row) {
    tlist_t *l = tlist_new();
    int x, y;
    ASSERT_EQ(1, tlist_add(l, 0, 1));
    ASSERT_EQ(1, tlist_add(l, 2, 3));
    ASSERT_EQ(1, tlist_top(l, &x, &y));
    ASSERT_EQ(x, 0);
    ASSERT_EQ(y, 1);
    ASSERT_EQ(1, tlist_top(l, &x, &y));
    ASSERT_EQ(x, 0);
    ASSERT_EQ(y, 1);
    ASSERT_EQ(l->size, 2);
    free(l);
}

TEST(Q11Push, many) {
    tlist_t *l = tlist_new();
    for (int i = 0; i < MAX_CAP; i++) {
        ASSERT_EQ(1, tlist_push(l, i, i));
    }
    ASSERT_EQ(l->size, MAX_CAP);
    // Check every element in the list
    std::tuple<int, int> *res = tlist_to_array(l);
    ASSERT_NE(nullptr, res);
    for (int i = 0; i < MAX_CAP; i++) {
        ASSERT_EQ(MAX_CAP - 1 - i, std::get<0>(res[i]));
        ASSERT_EQ(MAX_CAP - 1 - i, std::get<1>(res[i]));
    }
    free(l);
    free(res);
}

TEST(Q12Swap, not_in) {
    tlist_t *l = tlist_new();
    for (int i = 0; i < MAX_CAP; i++) {
        ASSERT_EQ(1, tlist_add(l, i, i));
    }
    ASSERT_EQ(0, tlist_swap(l, 1000, 11));
    ASSERT_EQ(l->size, MAX_CAP);
    free(l);
}

TEST(Q12, swap_hd_q) {
    tlist_t *l = tlist_new();
    for (int i = 0; i < MAX_CAP; i++) {
        ASSERT_EQ(1, tlist_add(l, i, i));
    }
    ASSERT_EQ(1, tlist_swap(l, 0, MAX_CAP - 1));
    ASSERT_EQ(l->size, MAX_CAP);
    ASSERT_EQ(get_hd(l)->x, MAX_CAP - 1);
    ASSERT_EQ(get_hd(l)->y, MAX_CAP - 1);
    ASSERT_EQ(get_last(l)->x, 0);
    ASSERT_EQ(get_last(l)->y, 0);
    // Check other elements
    std::tuple<int, int> *res = tlist_to_array(l);
    ASSERT_NE(nullptr, res);
    for (int i = 1; i < MAX_CAP - 1; i++) {
        ASSERT_EQ(i, std::get<0>(res[i]));
        ASSERT_EQ(i, std::get<1>(res[i]));
    }
    free(l);
}

TEST(Q13, no_modif) {
    tlist_t *l = tlist_new();
    for (int i = 0; i < MAX_CAP; i++) {
        ASSERT_EQ(1, tlist_add(l, i, i));
    }
    ASSERT_EQ(1, tlist_sort(l));
    ASSERT_EQ(l->size, MAX_CAP);
    // Check every element in the list
    std::tuple<int, int> *res = tlist_to_array(l);
    ASSERT_NE(nullptr, res);
    for (int i = 0; i < MAX_CAP; i++) {
        ASSERT_EQ(i, std::get<0>(res[i]));
        ASSERT_EQ(i, std::get<1>(res[i]));
    }
    free(l);
    free(res);
}

TEST(Q13, reverse_order) {
    tlist_t *l = tlist_new();
    for (int i = MAX_CAP - 1; i >= 0; i--) {
        ASSERT_EQ(1, tlist_add(l, i, i));
    }
    ASSERT_EQ(1, tlist_sort(l));
    ASSERT_EQ(l->size, MAX_CAP);
    // Check every element in the list
    std::tuple<int, int> *res = tlist_to_array(l);
    ASSERT_NE(nullptr, res);
    for (int i = 0; i < MAX_CAP; i++) {
        ASSERT_EQ(i, std::get<0>(res[i]));
        ASSERT_EQ(i, std::get<1>(res[i]));
    }
    free(l);
    free(res);
}

TEST(Q13, random_order) {
    int *arr = (int *) malloc(MAX_CAP * sizeof(int));
    for (int i = 0; i < MAX_CAP; i++) {
        arr[i] = i;
    }
    // Shuffle arr
    for (int i = 0; i < MAX_CAP; i++) {
        int j = rand() % MAX_CAP;
        int tmp = arr[i];
        arr[i] = arr[j];
        arr[j] = tmp;
    }
    tlist_t *l = tlist_new();
    for (int i = 0; i < MAX_CAP; i++) {
        ASSERT_EQ(1, tlist_add(l, arr[i], arr[i]));
    }
    ASSERT_EQ(1, tlist_sort(l));
    ASSERT_EQ(l->size, MAX_CAP);
    // Check every element in the list
    std::tuple<int, int> *res = tlist_to_array(l);
    ASSERT_NE(nullptr, res);
    for (int i = 0; i < MAX_CAP; i++) {
        ASSERT_EQ(i, std::get<0>(res[i]));
        ASSERT_EQ(i, std::get<1>(res[i]));
    }
    free(l);
    free(res);
    free(arr);
}