
#include "cells.h"
#include <stdlib.h>

t_sk_cell createSkCell(int val,int level){
    t_sk_cell *p;
    p = (t_sk_cell *)malloc(sizeof(t_sk_cell));
    p->value = val;
    p->level = level;
    //Ligne struct s_sk_cell à définir ?
    return *p;
}