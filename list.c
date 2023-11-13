#include "list.h"
#include <stdlib.h>


//Création des listes à niveaux vide
t_d_list *createList(int max_levels){
    t_d_list *list = (t_d_list *)malloc(sizeof(t_d_list));
    if (list != NULL) {
        list->head_0 = NULL;
        list->head_1 = (max_levels > 1) ? NULL : NULL;
    }
    return list;
}

//insertion d'une cellule en tête de liste
void insertCell(t_d_list *list, t_d_cell *cell, int level);

//Afficher l'ensemble des cellules pour un niveau donné
void displayListLevel(t_d_list *list, int level);

//Afficher l'ensemble des cellules sur l'ensemble des niveaux
void displayAllLevels(t_d_list *list);

//Optionnel : Afficher tous les niveaux de la liste, en alignant les cellules
void insertSorted(t_d_list *list, t_d_cell *cell);