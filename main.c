#include <stdio.h>
#include "cells.h"
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


    return 0;
}
