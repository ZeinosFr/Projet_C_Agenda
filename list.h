#ifndef UNTITLED4_LIST_H
#define UNTITLED4_LIST_H
#include "cells.h"

t_sk_list *createList(int max_level);
void insertCell(t_sk_list *list, t_sk_cell *cell);
void displayListLevel(t_sk_list *list, int level);
void displayAllLevels(t_sk_list *list);
void insertSorted(t_sk_list *list, t_sk_cell *cell);

#endif //UNTITLED4_LIST_H
