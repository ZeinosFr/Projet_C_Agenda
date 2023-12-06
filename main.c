#include <stdio.h>
#include <stdlib.h>
#include "cells.h"
#include "list.h"
#include "timer.h"

int main() {
    // Create a list with 5 levels
    t_sk_list *myList = createList(5);

    // Insert cells at various levels
    insertCell(myList, createSkCell(5, 2));
    insertCell(myList, createSkCell(8, 2));
    insertCell(myList, createSkCell(3, 2));
    insertCell(myList, createSkCell(10, 2));
    displayAllLevels(myList);

    t_sk_list *ma_liste_a_niveaux = initialiser_liste_a_niveaux(6);

    // Afficher la liste à niveaux
    afficher_liste_a_niveaux(ma_liste_a_niveaux);
    // Display levels
    // Mesurer le temps pour 1000 recherches avec une valeur aléatoire
    int numSearches = 10000;
    int randomValue = 1;// Valeur aléatoire entre 1 et 8
    measureSearchTime(ma_liste_a_niveaux, randomValue, numSearches);

    //----------------------CREATION DU GRAPHIQUE--------------------------//
    return 0;
}
