//
// Created by Kenny on 09/12/2023.
//

#ifndef UNTITLED4_AGENDA_H
#define UNTITLED4_AGENDA_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cells.h"

typedef struct {
    int day;
    int month;
    int year;
} Date;

typedef struct {
    int hour;
    int minute;
} Time;

typedef struct Rendezvous {
    Date date;
    Time startTime;
    Time endTime;
    char *subject;
    struct Rendezvous *next;
} Rendezvous;

typedef struct {
    char *nom;
    char *prenom;
} Contact;


typedef struct AgendaEntry {
    Contact *contact;
    Rendezvous *rendezvousList;
    struct AgendaEntry *nextLevel;
    struct AgendaEntry *next;
} AgendaEntry;
typedef struct SearchResult {
    AgendaEntry *entry;
    struct SearchResult *next;
} SearchResult;


char **readNamesFromFile(const char *filename, int *numNames);
char **readFirstNamesFromFile(const char *filename, int *numFirstNames);
Contact *createContact(const char *nom, const char *prenom);
AgendaEntry *generateContactsList(char **lastNames, int numLastNames, char **firstNames, int numFirstNames);
void displayContactsList(AgendaEntry *head);

void searchContactPartial(AgendaEntry *head, const char *partialName);

void freeContactsList(AgendaEntry *head);

void displayAppointments(AgendaEntry *head);

void createNewContact(AgendaEntry **head);
void insertContact(AgendaEntry **head, AgendaEntry *newEntry);

AgendaEntry *createAgendaEntry(Contact *contact);
AgendaEntry *searchContact(AgendaEntry *head, const char *nom, const char *prenom);
Rendezvous *createRendezvous(Date date, Time startTime, Time endTime, const char *subject);
AgendaEntry *createOrUpdateContactWithAppointment(AgendaEntry **head, const char *nom, const char *prenom, Date date, Time startTime, Time endTime, const char *subject);
#endif //UNTITLED4_AGENDA_H
