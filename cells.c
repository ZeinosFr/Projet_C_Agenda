#include <stdio.h>
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

    // Ajouter les cellules dans la liste
    for (int i = 1; i <= (1 << n) - 1; i++) {
        t_sk_cell *new_cell = (t_sk_cell *)malloc(sizeof(t_sk_cell));
        new_cell->value = i;
        new_cell->level = 0;
        new_cell->next = (t_sk_cell **)malloc(sizeof(t_sk_cell *) * n);

        for (int j = 0; j < n; j++) {
            new_cell->next[j] = NULL;
        }

        // Ajouter la nouvelle cellule à chaque niveau
        int count = 0;
        int temp = i;
        while (temp % 2 == 0) {
            temp /= 2;
            count++;
        }

        for (int j = 0; j <= count; j++) {
            new_cell->next[j] = liste_a_niveaux->heads->next[j];
            liste_a_niveaux->heads->next[j] = new_cell;
        }
    }

    return liste_a_niveaux;
}

// Fonction pour afficher la liste à niveaux
void afficher_liste_a_niveaux(t_sk_list *liste_a_niveaux) {
    printf("Liste a Niveaux:\n");

    for (int i = 0; i < liste_a_niveaux->max_level; i++) {
        printf("Level %d: ", i);

        t_sk_cell *current = liste_a_niveaux->heads->next[i];

        while (current != NULL) {
            printf("%d ", current->value);
            current = current->next[i];
        }

        printf("\n");
    }
}

t_sk_cell *searchLevel0(t_sk_list *list, int value) {
    t_sk_cell *current = list->heads->next[0];

    while (current != NULL) {
        if (current->value == value) {
            return current;
        }
        current = current->next[0];
    }

    return NULL; // Valeur non trouvée
}

t_sk_cell *searchFromTopLevel(t_sk_list *list, int value) {
    for (int i = list->max_level - 1; i >= 0; i--) {
        t_sk_cell *current = list->heads->next[i];

        while (current != NULL) {
            if (current->value == value) {
                return current;
            } else if (current->value < value) {
                break; // La valeur recherchée est supérieure, descendre au niveau inférieur
            }
            current = current->next[i];
        }
    }

    return NULL; // Valeur non trouvée
}

