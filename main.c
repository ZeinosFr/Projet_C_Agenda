#include <stdio.h>
#include <stdlib.h>
#include "cells.h"
#include "list.h"
#include "timer.h"
#include "agenda.h"
#include <string.h>
#define MAX_NAME_LENGTH 256
#define MAX_SUBJECT_LENGTH 512


int main() {

    // Changer le paramètre n pour changer la taille de la liste
    t_sk_list *myList = createList(5);
    printf("----------Creation de liste---------------\n");
    // Insertion de cellule à un niveau précis
    insertCell(myList, createSkCell(5, 1));
    insertCell(myList, createSkCell(8, 3));
    insertCell(myList, createSkCell(3, 1));
    insertCell(myList, createSkCell(10, 4));
    displayAllLevels(myList);


    printf("--------Creation de liste a niveau ----------\n");
    //-----------------------CREATION LISTE A NIVEAU----------------------//
    t_sk_list *ma_liste_a_niveaux = initialiser_liste_a_niveaux(6);
    // Afficher la liste à niveaux
    afficher_liste_a_niveaux(ma_liste_a_niveaux);

    //----------------------CREATION DU GRAPHIQUE--------------------------//


    printf("----------------Recherche et creation du graphique-----------------\n");
    srand(time(NULL));
    measureAndLogTime();


//-------------------------------------PARTIE 3-------------------------------//
    printf("--------------------------------PARTIE AGENDA---------------------\n");
    // Lire les noms à partir du fichier
    int numLastNames;
    char contactNom[MAX_NAME_LENGTH];
    char contactPrenom[MAX_NAME_LENGTH];
    Date date;
    Time startTime, endTime;
    char subject[MAX_SUBJECT_LENGTH];
    char **lastNames = readNamesFromFile("../nat2021.csv", &numLastNames);
    int numFirstNames;
    char **firstNames = readFirstNamesFromFile("../noms2008nat_txt.txt", &numFirstNames);
    // Générer la liste de contacts à partir de noms et prénoms
    AgendaEntry *contactsList = generateContactsList(lastNames, numLastNames, firstNames, numFirstNames);
    char partialName[256];

    int choice;
    do {
        printf("\nMenu:\n");
        printf("1. Rechercher un contact\n");
        printf("2. Afficher les rendez-vous d'un contact\n");
        printf("3. Creer un contact\n");
        printf("4. Creer un rendez-vous pour un contact\n");
        printf("0. Quitter\n");

        printf("Choix : ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                // Rechercher un contact
                printf("Entrez une partie du nom : ");
                getchar();
                fgets(partialName, sizeof(partialName), stdin);
                partialName[strcspn(partialName, "\n")] = '\0';  // Supprimer le retour à la ligne

                // Rechercher des contacts par nom partiel (sensible à la casse)
                searchContactPartial(contactsList, partialName);
                break;
            case 2:
                // Afficher les rendez-vous d'un contact
                displayAppointments(contactsList);
                break;
            case 3:
                // Créer un contact
                createNewContact(&contactsList);
                break;
            case 4:
                // Créer un rendez-vous pour un contact
                printf("\nSaisissez les informations pour le rendez-vous :\n");
                printf("Nom du contact : ");
                getchar();
                fgets(contactNom, sizeof(contactNom), stdin);
                contactNom[strcspn(contactNom, "\n")] = '\0';  // Supprimer le retour à la ligne

                printf("Prenom du contact : ");
                fgets(contactPrenom, sizeof(contactPrenom), stdin);
                contactPrenom[strcspn(contactPrenom, "\n")] = '\0';  // Supprimer le retour à la ligne

                printf("Date du rendez-vous (jj mm aaaa) : ");
                scanf("%d %d %d", &date.day, &date.month, &date.year);

                printf("Heure de debut (hh mm) : ");
                scanf("%d %d", &startTime.hour, &startTime.minute);

                printf("Heure de fin (hh mm) : ");
                scanf("%d %d", &endTime.hour, &endTime.minute);

                printf("Objet du rendez-vous : ");
                getchar();  // Absorber le caractère de nouvelle ligne restant
                fgets(subject, sizeof(subject), stdin);
                subject[strcspn(subject, "\n")] = '\0';  // Supprimer le retour à la ligne

                // Création ou mise à jour du contact avec le rendez-vous
                createOrUpdateContactWithAppointment(&contactsList, contactNom, contactPrenom, date, startTime, endTime, subject);
                break;
            case 0:
                // Quitter le programme
                break;
            default:
                printf("Choix invalide. Veuillez entrer un nombre entre 0 et 8.\n");
                break;
        }

    } while (choice != 0);

    // Libérer la mémoire
    for (int i = 0; i < numLastNames; i++) {
        free(lastNames[i]);
    }
    free(lastNames);

    for (int i = 0; i < numFirstNames; i++) {
        free(firstNames[i]);
    }
    free(firstNames);
    freeContactsList(contactsList);

    return 0;
}
