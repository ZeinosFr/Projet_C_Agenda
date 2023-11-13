#include <stdio.h>
#include "cells.c"
#include "list.c"
#include "cells.h"
#include "timer.c"
#include "list.h"
int main() {
    // Create a list with 5 levels
    t_sk_list *myList = createList(5);

    // Insert cells at various levels
    insertCell(myList, createSkCell(5, 2));
    insertCell(myList, createSkCell(8, 2));
    insertCell(myList, createSkCell(3, 2));
    insertCell(myList, createSkCell(10, 2));

    // Display levels
    displayAllLevels(myList);

    t_sk_list *ma_liste_a_niveaux = initialiser_liste_a_niveaux(3);

    // Afficher la liste à niveaux
    afficher_liste_a_niveaux(ma_liste_a_niveaux);

    return 0;
}
