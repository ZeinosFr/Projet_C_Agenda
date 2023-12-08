#include <stdio.h>
#include <stdlib.h>
#include "cells.h"
#include "list.h"
#include "timer.h"

int main() {
    // Changer le paramètre n pour changer la taille de la liste
    t_sk_list *myList = createList(5);

    // Insertion de cellule à un niveau précis
    insertCell(myList, createSkCell(5, 1));
    insertCell(myList, createSkCell(8, 3));
    insertCell(myList, createSkCell(3, 1));
    insertCell(myList, createSkCell(10, 4));
    displayAllLevels(myList);

    //t_sk_list *ma_liste_a_niveaux = initialiser_liste_a_niveaux(4);
    // Afficher la liste à niveaux
    //afficher_liste_a_niveaux(ma_liste_a_niveaux);

    //----------------------CREATION DU GRAPHIQUE--------------------------//
    measureAndLogTime();

    return 0;
}
