#ifndef UNTITLED4_LIST_H
#define UNTITLED4_LIST_H
#include "cells.h"

t_d_list *createList(int max_levels);
void insertCell(t_d_list *list, t_d_cell *cell, int level);
void displayListLevel(t_d_list *list, int level);
void displayAllLevels(t_d_list *list);
void insertSorted(t_d_list *list, t_d_cell *cell);

#endif //UNTITLED4_LIST_H
