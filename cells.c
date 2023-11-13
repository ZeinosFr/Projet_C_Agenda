
#include "cells.h"
#include <stdlib.h>

t_sk_cell *createSkCell(int val, int level) {
    t_sk_cell *p = (t_sk_cell *)malloc(sizeof(t_sk_cell));
    if (p != NULL) {
        p->value = val;
        p->level = level;
        p->next = (t_sk_cell **)malloc(level * sizeof(t_sk_cell *));

        // Initialiser tous les pointeurs à NULL
        for (int i = 0; i < level; i++) {
            p->next[i] = NULL;
        }
    }
    return p;
}