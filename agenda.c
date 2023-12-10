//
// Created by Kenny on 09/12/2023.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "agenda.h"
#include <ctype.h>
#define MAX_NAME_LENGTH 256


char **readNamesFromFile(const char *filename, int *numNames) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Erreur lors de l'ouverture du fichier");
        exit(EXIT_FAILURE);
    }

    char buffer[256];
    int count = 0;

    // Compter le nombre de noms dans le fichier
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        count++;
    }

    // Allouer de la mémoire pour stocker les noms
    char **names = (char **)malloc(count * sizeof(char *));
    rewind(file);

    // Lire les noms et les stocker dans le tableau
    for (int i = 0; i < count; i++) {
        fgets(buffer, sizeof(buffer), file);
        buffer[strcspn(buffer, "\n")] = '\0';  // Supprimer le retour à la ligne
        names[i] = strdup(buffer);
    }

    fclose(file);
    *numNames = count;
    return names;
}

// Fonction pour lire les prénoms à partir du fichier texte
char **readFirstNamesFromFile(const char *filename, int *numFirstNames) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Erreur lors de l'ouverture du fichier");
        exit(EXIT_FAILURE);
    }

    char buffer[256];
    int count = 0;

    // Compter le nombre de prénoms dans le fichier
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        count++;
    }

    // Allouer de la mémoire pour stocker les prénoms
    char **firstNames = (char **)malloc(count * sizeof(char *));
    rewind(file);

    // Lire les prénoms et les stocker dans le tableau
    for (int i = 0; i < count; i++) {
        fgets(buffer, sizeof(buffer), file);
        buffer[strcspn(buffer, "\n")] = '\0';  // Supprimer le retour à la ligne
        firstNames[i] = strdup(buffer);
    }

    fclose(file);
    *numFirstNames = count;
    return firstNames;
}

// Fonction pour créer un contact à partir d'un nom et d'un prénom
Contact *createContact(const char *nom, const char *prenom) {
    Contact *newContact = (Contact *)malloc(sizeof(Contact));
    if (!newContact) {
        perror("Erreur d'allocation mémoire");
        exit(EXIT_FAILURE);
    }

    newContact->nom = strdup(nom);
    newContact->prenom = strdup(prenom);

    return newContact;
}

// Fonction pour générer une liste de contacts à partir de noms et prénoms
AgendaEntry *generateContactsList(char **lastNames, int numLastNames, char **firstNames, int numFirstNames) {
    AgendaEntry *head = NULL;
    AgendaEntry *current = NULL;

    for (int i = 0; i < numLastNames && i < numFirstNames; i++) {
        Contact *newContact = createContact(lastNames[i], firstNames[i]);

        AgendaEntry *newEntry = (AgendaEntry *)malloc(sizeof(AgendaEntry));
        if (!newEntry) {
            perror("Erreur d'allocation mémoire");
            exit(EXIT_FAILURE);
        }

        newEntry->contact = newContact;
        newEntry->next = NULL;

        if (!head) {
            head = newEntry;
            current = newEntry;
        } else {
            current->next = newEntry;
            current = newEntry;
        }
    }

    return head;
}

// Fonction pour afficher la liste des contacts
void displayContactsList(AgendaEntry *head) {
    printf("Liste des contacts:\n");

    AgendaEntry *current = head;
    while (current != NULL) {
        printf("Nom: %s, Prenom: %s\n", current->contact->nom, current->contact->prenom);
        current = current->next;
    }
}


//-----------------------------------Recherche de contact------------------------------//
void searchContactPartial(AgendaEntry *head, const char *partialName) {
    AgendaEntry *current = head;
    int trouver = 0;
    printf("Resultats de la recherche pour \"%s\":\n", partialName);

    int exactMatchFound = 0;

    // Convertir la saisie partielle en minuscules
    char partialNameLower[MAX_NAME_LENGTH];
    for (int i = 0; partialName[i] != '\0'; i++) {
        partialNameLower[i] = toupper(partialName[i]);
    }
    partialNameLower[strlen(partialName)] = '\0';

    while (current != NULL) {
        // Utiliser strncmp pour rechercher le nom partiel (insensible à la casse)
        if (strncmp(current->contact->nom, partialNameLower, strlen(partialNameLower)) == 0) {
            // Si le nom du contact commence par la saisie partielle, on le considère comme une correspondance
            printf("%s %s\n", current->contact->nom, current->contact->prenom);

            // Vérifier si c'est une correspondance exacte
            if (strcmp(current->contact->nom, partialNameLower) == 0) {
                exactMatchFound = 1;
            }
        }
        current = current->next;
        trouver = 1;
    }

    if (!exactMatchFound && trouver == 0) {
        printf("Aucun contact ne correspond ou ne commence par \"%s\".\n", partialName);
    }
}

// Fonction pour libérer la mémoire de la liste de contacts
void freeContactsList(AgendaEntry *head) {
    AgendaEntry *current = head;
    while (current != NULL) {
        AgendaEntry *next = current->next;
        free(current->contact->nom);
        free(current->contact->prenom);
        free(current->contact);
        free(current);
        current = next;
    }
}

//---------------------------------PARTIE AGENDA--------------------------//
void displayAppointments(AgendaEntry *head) {
    char contactName[MAX_NAME_LENGTH];
    printf("Entrez le NOM PRENOM du contact : ");
    getchar();
    fgets(contactName, sizeof(contactName), stdin);
    contactName[strcspn(contactName, "\n")] = '\0';  // Supprimer le retour à la ligne

    char contactNom[MAX_NAME_LENGTH];
    char contactPrenom[MAX_NAME_LENGTH];

    // Extraire le nom et le prénom de la saisie
    if (sscanf(contactName, "%s %s", contactNom, contactPrenom) != 2) {
        printf("Format incorrect. Utilisez le format 'Nom Prenom'.\n");
        return;
    }

    // Convertir le nom et le prénom en minuscules pour la comparaison
    for (int i = 0; contactNom[i] != '\0'; i++) {
        contactNom[i] = toupper(contactNom[i]);
    }

    for (int i = 0; contactPrenom[i] != '\0'; i++) {
        contactPrenom[i] = toupper(contactPrenom[i]);
    }

    AgendaEntry *current = head;

    // Parcourir la liste pour trouver le contact
    while (current != NULL) {
        // Convertir le nom et le prénom du contact en minuscules pour la comparaison
        char lowerCurrentNom[MAX_NAME_LENGTH];
        char lowerCurrentPrenom[MAX_NAME_LENGTH];

        strcpy(lowerCurrentNom, current->contact->nom);
        strcpy(lowerCurrentPrenom, current->contact->prenom);

        for (int i = 0; lowerCurrentNom[i] != '\0'; i++) {
            lowerCurrentNom[i] = toupper(lowerCurrentNom[i]);
        }

        for (int i = 0; lowerCurrentPrenom[i] != '\0'; i++) {
            lowerCurrentPrenom[i] = toupper(lowerCurrentPrenom[i]);
        }

        // Si le contact correspond, afficher les rendez-vous
        if (strcmp(lowerCurrentNom, contactNom) == 0 && strcmp(lowerCurrentPrenom, contactPrenom) == 0) {
            printf("Rendez-vous pour %s %s:\n", current->contact->nom, current->contact->prenom);

            // Parcourir les rendez-vous du contact
            Rendezvous *appointment = current->rendezvousList;
            while (appointment != NULL) {
                printf("Date: %02d/%02d/%04d\n", appointment->date.day, appointment->date.month, appointment->date.year);
                printf("Heure de debut: %02d:%02d\n", appointment->startTime.hour, appointment->startTime.minute);
                printf("Heure de fin: %02d:%02d\n", appointment->endTime.hour, appointment->endTime.minute);
                printf("Objet: %s\n", appointment->subject);

                appointment = appointment->next;
            }

            return; // Finir la fonction après avoir affiché les rendez-vous du contact
        }

        current = current->next;
    }

    // Si on arrive ici, le contact n'a pas été trouvé
    printf("Contact non trouve : %s\n", contactName);
}

//-------------------------------------------------AJOUTER CONTACT----------------------------------------------//

void insertContact(AgendaEntry **head, AgendaEntry *newEntry) {
    // Si la liste est vide, le nouveau contact devient la tête de la liste
    if (*head == NULL) {
        *head = newEntry;
        newEntry->next = NULL;
    } else {
        // Sinon, parcourir la liste jusqu'à la fin
        AgendaEntry *current = *head;
        while (current->next != NULL) {
            current = current->next;
        }

        // Insérer le nouveau contact à la fin de la liste
        current->next = newEntry;
        newEntry->next = NULL;
    }
}

// Fonction pour créer un contact avec insertion dans la liste
void createNewContact(AgendaEntry **head) {
    // Saisir le nom et le prénom du contact
    char nom[MAX_NAME_LENGTH];
    char prenom[MAX_NAME_LENGTH];

    printf("Entrez le NOM du contact : ");
    getchar();
    fgets(nom, sizeof(nom), stdin);
    nom[strcspn(nom, "\n")] = '\0';  // Supprimer le retour à la ligne

    printf("Entrez le PRENOM du contact : ");
    fgets(prenom, sizeof(prenom), stdin);
    prenom[strcspn(prenom, "\n")] = '\0';  // Supprimer le retour à la ligne

    // Convertir le nom et le prénom en minuscules pour l'insertion
    for (int i = 0; nom[i] != '\0'; i++) {
        nom[i] = toupper(nom[i]);
    }

    for (int i = 0; prenom[i] != '\0'; i++) {
        prenom[i] = toupper(prenom[i]);
    }

    // Créer un nouveau contact en utilisant la fonction existante
    Contact *newContact = createContact(nom, prenom);

    // Créer une nouvelle entrée d'agenda pour le contact
    AgendaEntry *newEntry = (AgendaEntry *)malloc(sizeof(AgendaEntry));
    if (!newEntry) {
        perror("Erreur d'allocation memoire pour l'entree d'agenda");
        exit(EXIT_FAILURE);
    }

    newEntry->contact = newContact;
    newEntry->rendezvousList = NULL;  // Initialise la liste de rendez-vous à NULL

    // Insérer le contact dans la liste à niveaux
    insertContact(head, newEntry);

    printf("Contact ajoute avec succes : %s %s\n", newContact->nom, newContact->prenom);
}


//----------------------------------PARTIE RENDEZ VOUS----------------------------------//

AgendaEntry *createAgendaEntry(Contact *contact) {
    // Allouer de la mémoire pour la nouvelle entrée d'agenda
    AgendaEntry *newEntry = (AgendaEntry *)malloc(sizeof(AgendaEntry));
    if (!newEntry) {
        perror("Erreur d'allocation mémoire pour l'entrée d'agenda");
        exit(EXIT_FAILURE);
    }

    // Initialiser les champs de l'entrée d'agenda avec le contact fourni
    newEntry->contact = contact;
    newEntry->rendezvousList = NULL;
    newEntry->nextLevel = NULL;
    newEntry->next = NULL;

    return newEntry;
}

AgendaEntry *searchContact(AgendaEntry *head, const char *nom, const char *prenom) {
    // Convertir les noms et prénoms en majuscules pour la recherche
    char upperNom[MAX_NAME_LENGTH];
    char upperPrenom[MAX_NAME_LENGTH];

    for (int i = 0; nom[i] != '\0'; i++) {
        upperNom[i] = toupper(nom[i]);
    }
    upperNom[strlen(nom)] = '\0';

    for (int i = 0; prenom[i] != '\0'; i++) {
        upperPrenom[i] = toupper(prenom[i]);
    }
    upperPrenom[strlen(prenom)] = '\0';

    AgendaEntry *current = head;

    while (current != NULL) {
        // Utiliser strcmp pour rechercher le nom et prénom (insensibles à la casse)
        if (strcmp(current->contact->nom, upperNom) == 0 && strcmp(current->contact->prenom, upperPrenom) == 0) {
            return current;  // Contact trouvé
        }
        current = current->next;
    }

    return NULL;  // Contact non trouvé
}

Rendezvous *createRendezvous(Date date, Time startTime, Time endTime, const char *subject) {
    // Allouer de la mémoire pour le nouveau rendez-vous
    Rendezvous *newRendezvous = (Rendezvous *)malloc(sizeof(Rendezvous));
    if (!newRendezvous) {
        perror("Erreur d'allocation mémoire pour le rendez-vous");
        exit(EXIT_FAILURE);
    }

    // Initialiser les champs du rendez-vous avec les valeurs fournies
    newRendezvous->date = date;
    newRendezvous->startTime = startTime;
    newRendezvous->endTime = endTime;
    newRendezvous->subject = strdup(subject);
    newRendezvous->next = NULL;

    return newRendezvous;
}

AgendaEntry *createOrUpdateContactWithAppointment(AgendaEntry **head, const char *nom, const char *prenom, Date date, Time startTime, Time endTime, const char *subject) {
    // Chercher le contact dans la liste
    AgendaEntry *contactEntry = searchContact(*head, nom, prenom);

    // Si le contact n'existe pas, le créer
    if (contactEntry == NULL) {
        Contact *newContact = createContact(nom, prenom);
        AgendaEntry *newEntry = createAgendaEntry(newContact);
        insertContact(head, newEntry);
        contactEntry = newEntry;
    }

    // Créer le rendez-vous
    Rendezvous *newRendezvous = createRendezvous(date, startTime, endTime, subject);

    // Insérer le rendez-vous dans la liste des rendez-vous du contact
    newRendezvous->next = contactEntry->rendezvousList;
    contactEntry->rendezvousList = newRendezvous;

    return contactEntry;
}