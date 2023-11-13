
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
t_sk_list *initialiser_liste_a_niveaux(int n) {
    // Créer la liste à niveaux
    t_sk_list *liste_a_niveaux = (t_sk_list *)malloc(sizeof(t_sk_list));
    liste_a_niveaux->max_level = n;

    // Initialiser la tête de chaque niveau
    liste_a_niveaux->heads = (t_sk_cell *)malloc(sizeof(t_sk_cell));
    liste_a_niveaux->heads->value = 0;
    liste_a_niveaux->heads->level = n - 1;
    liste_a_niveaux->heads->next = (t_sk_cell **)malloc(sizeof(t_sk_cell *) * n);

    for (int i = 0; i < n; i++) {
        liste_a_niveaux->heads->next[i] = NULL;
    }

    // Ajouter 2*n - 2 valeurs supplémentaires initialisées à 0
    for (int i = 0; i < 2 * n - 2; i++) {
        t_sk_cell *new_cell = (t_sk_cell *)malloc(sizeof(t_sk_cell));
        new_cell->value = 0;
        new_cell->level = n - 1;
        new_cell->next = (t_sk_cell **)malloc(sizeof(t_sk_cell *) * n);

        for (int j = 0; j < n; j++) {
            new_cell->next[j] = NULL;
        }

        // Ajouter la nouvelle cellule à chaque niveau
        for (int j = 0; j < n; j++) {
            new_cell->next[j] = liste_a_niveaux->heads->next[j];
            liste_a_niveaux->heads->next[j] = new_cell;
        }
    }

    return liste_a_niveaux;
}

// Fonction pour afficher la liste à niveaux
void afficher_liste_a_niveaux(t_sk_list *liste_a_niveaux) {
    printf("Liste à Niveaux:\n");
    for (int i = liste_a_niveaux->max_level - 1; i >= 0; i--) {
        printf("Level %d: ", i);
        t_sk_cell *current = liste_a_niveaux->heads->next[i];
        while (current != NULL) {
            printf("%d ", current->value);
            current = current->next[i];
        }
        printf("\n");
    }
}
