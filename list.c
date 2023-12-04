#include "list.h"
#include <stdlib.h>
#include <stdio.h>


//Création des listes à niveaux vide
t_sk_list *createList(int max_level) {
    t_sk_list *list = (t_sk_list *)malloc(sizeof(t_sk_list));
    if (list != NULL) {
        list->heads = (t_sk_cell *)malloc(max_level * sizeof(t_sk_cell));
        for (int i = 0; i < max_level; i++) {
            list->heads[i].value = 0;  // Set a sentinel value for the head
            list->heads[i].level = i;
            list->heads[i].next = NULL;
        }
        list->max_level = max_level;
    }
    return list;
}


//insertion d'une cellule en tête de liste
void insertCell(t_sk_list *list, t_sk_cell *cell){
    for (int i = 0; i < cell->level; i++) {
        cell->next[i] = list->heads[i].next;
        list->heads[i].next = cell;
    }
}

//Afficher l'ensemble des cellules pour un niveau donné
void displayListLevel(t_sk_list *list, int level){
    if (level < 0 || level >= list->max_level) {
        printf("Invalid level.\n");
        return;
    }

    t_sk_cell *current = list->heads[level].next;

    while (current != NULL) {
        printf("[%d] -> ", current->value);
        current = current->next[level];
    }
    printf("NULL\n");
}


//Afficher l'ensemble des cellules sur l'ensemble des niveaux
void displayAllLevels(t_sk_list *list){
    for (int i = 0; i < list->max_level; i++) {
        printf("Level %d: ", i);
        displayListLevel(list, i);
    }
}

//Optionnel : Afficher tous les niveaux de la liste, en alignant les cellules
void insertSorted(t_sk_list *list, t_sk_cell *cell) {
    for (int i = 0; i < list->max_level; i++) {
        // Trouver la position d'insertion au niveau i
        t_sk_cell *prev = &list->heads[i];
        t_sk_cell *current = prev->next[i];

        while (current != NULL && current->value < cell->value) {
            prev = current;
            current = current->next[i];
        }

        // Insérer la cellule au niveau i
        cell->next[i] = current;
        prev->next[i] = cell;
    }
}




