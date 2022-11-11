#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

//Q1
typedef struct hnode_t {
    int value;
    struct hnode_t *left;
    struct hnode_t *right;
    struct hnode_t *top;
    struct hnode_t *bottom;
} hnode_t;

//Q2
typedef struct hlist_t {
    hnode_t *head;
    int height;
} hlist_t;

//Q3
hlist_t *hlist_new() {
    hlist_t *hlist = malloc(sizeof(hlist_t));
    hnode_t *inf = malloc(sizeof(hnode_t));
    inf->value = INT_MAX;
    inf->right = inf->bottom = inf->top = inf->top = NULL;
    hnode_t *head = malloc(sizeof(hnode_t));
    head->value = INT_MIN;
    head->left = head->top = head->bottom = NULL;
    head->right = inf;
    inf->left = head;
    hlist->height = 1;
    hlist->head = head;
    return hlist;
}

//Q4
void hlist_free(hlist_t *hlist) {
    hnode_t *curr_vert = hlist->head;
    while (curr_vert != NULL) {
        hnode_t *curr_hor = curr_vert->right;
        while (curr_hor != NULL) {
            hnode_t *temp = curr_hor;
            curr_hor = curr_hor->right;
            free(temp);
        }
        hnode_t *temp = curr_vert;
        curr_vert = curr_vert->bottom;
        free(temp);
    }
}

//Q5
int hlist_search(hlist_t *l, int v, hnode_t *path[]) {
    hnode_t *current_node = l->head;
    int i = 0;
    while (current_node != NULL) {
        int right_val = current_node->right->value;
        if (right_val > v) {
            path[i] = current_node;
            i++;
            current_node = current_node->bottom;
        } else {
            current_node = current_node->right;
        }
    }
    int res = path[l->height - 1]->value == v;
    return res;
}

//Q6
int hlist_add(hlist_t *l, int v) {
    if (v == INT_MAX || v == INT_MIN) { // We don't allow those values as they are our bounds
        return 0;
    }
    hnode_t **path = malloc(sizeof(hnode_t) * l->height);
    hlist_search(l, v, path);
    int i = l->height - 1;
    hnode_t *last = NULL;
    while (i >= 0) {
        hnode_t *new_node = malloc(sizeof(hnode_t));
        new_node->value = v;
        new_node->left = path[i];
        new_node->right = path[i]->right;
        new_node->right->left = new_node;
        path[i]->right = new_node;
        new_node->top = new_node->bottom = NULL;
        if (last != NULL) {
            last->top = new_node;
            new_node->bottom = last;
        }
        last = new_node;
        i--;
        if (rand() > (RAND_MAX / 2)) {// Real random bool NOLINT(cert-msc50-cpp)
            break;
        }
    }
    if (i == -1) {
        hnode_t *new_left = malloc(sizeof(hnode_t));
        hnode_t *new_right = malloc(sizeof(hnode_t));
        new_left->value = INT_MIN;
        new_right->value = INT_MAX;
        new_left->right = new_right;
        new_right->left = new_left;
        new_left->bottom = path[0];
        new_right->bottom = path[0]->right->right;
        path[0]->top = new_left;
        path[0]->right->right->top = new_right;
        new_left->top = new_left->left = new_right->top = new_right->right = NULL;
        l->head = new_left;
        l->height++;
    }
    free(path);
    return 1;

}

//Q7
int hlist_remove(hlist_t *l, int v) {
    if (v == INT_MIN || v == INT_MAX) {
        return 0;
    }
    hnode_t **path = malloc(sizeof(hnode_t) * l->height);
    hlist_search(l, v, path);
    int i = l->height - 1;
    int res = 0;
    bool first_complete_remove = true;
    for (; i >= 0; i--) {
        if (path[i]->value != v) {
            break;
        }
        res = 1;
        path[i]->left->right = path[i]->right;
        path[i]->right->left = path[i]->left;
        if (path[i]->left->value == INT_MIN && path[i]->right->value == INT_MAX && i) {
            if (first_complete_remove) {
                first_complete_remove = false;
                l->head->bottom = path[i]->left->bottom;
                l->head->right->bottom = path[i]->right->bottom;
                if (l->height > 2) {
                    path[i]->left->bottom->top = l->head;
                    path[i]->right->bottom->top = l->head->right;
                }
            }
            free(path[i]->right);
            free(path[i]->left);
            l->height--;
        }
        free(path[i]);
    }
    free(path);
    return res;
}

void hlist_print(hlist_t *l) {
    hnode_t *curr_vert = l->head;
    while (curr_vert != NULL) {
        hnode_t *curr_hor = curr_vert;
        while (curr_hor != NULL) {
            if (curr_hor->value == INT_MAX) {
                printf("+inf");
            } else if (curr_hor->value == INT_MIN) {
                printf("-inf ");
            } else {
                printf("%d ", curr_hor->value);
            }
            curr_hor = curr_hor->right;
        }
        printf("\n");
        curr_vert = curr_vert->bottom;
    }
}
//Q8 Dans le fichier main_exo2.c
