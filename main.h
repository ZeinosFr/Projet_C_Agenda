//
// Created by Kenny on 23/10/2023.
//

#ifndef UNTITLED4_MAIN_H
#define UNTITLED4_MAIN_H

typedef struct s_d_cell
{
    int value;
    struct s_d_cell *next_0;
    struct s_d_cell *next_1;
} t_d_cell;

typedef struct s_d_list
{
    t_d_cell *head_0;
    t_d_cell *head_1;
} t_d_list;

typedef struct s_sk_cell{
    int value;
    int level;
    struct s_sk_cell ** next;
}t_sk_cell;

typedef struct s_sk_list{
    t_sk_cell heads;
    int max_level;
}t_sk_list;


//Création de la cellule

t_sk_cell createSkCell(int val,int level){
    t_sk_cell p;
    p.value = val;
    p.level = level;
    //Ligne struct s_sk_cell à définir ?
    return p;
}
//Je crois c'est faux donc a vérifier (createSklistempty)
void createSklistempty(int level_max){
    t_sk_list p;
    p.max_level = level_max;
    p.heads.level = NULL;
// comment faire pour dire que la suite est NULL ?

}
#endif //UNTITLED4_MAIN_H
