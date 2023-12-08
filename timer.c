//
// Created by flasque on 11/10/2023.
//

#include <stdio.h>
#include <malloc.h>
#include "timer.h"
#include "cells.h"

// start the timer
void startTimer()
{
    _timer._start = clock();
}

// stop the timer and compute the duration in milliseconds
void stopTimer()
{
    _timer._end = clock();
    // compute the duration in milliseconds wrt CLOCKS_PER_SEC
    _timer._msecs = (1000.0 * (double) (_timer._end - _timer._start)) / CLOCKS_PER_SEC;
}

// display the time
void displayTime()
{
    // display the time using getTimeAsString()
    printf("%s\n", getTimeAsString());
    return;
}

// return a string with the time in seconds and milliseconds
char *getTimeAsString()
{
    // return a string with the time in seconds and milliseconds
    // format : integers, with 3 digits, fill with 0
    // example : 001,123

    // use sprintf to write the string in a dynamically allocated buffer
    char *buffer = (char *)malloc(10*sizeof(char));
    // use sprintf to write the string in a dynamically allocated buffer
    sprintf(buffer, "%03d,%03d", (int)(_timer._msecs)/1000, (int)(_timer._msecs)%1000);

    // return the buffer
    return buffer;
}

void measureAndLogTime() {
    FILE *log_file = fopen("log.txt", "w");
    char format[] = "%d\t%s\t%s\n" ;
    int initial_level = 7;
    int final_level = 16;
    int numSearches = 10000;
    for (int level = initial_level; level <= final_level; level++) {
        // Initialiser la liste à niveaux
        t_sk_list *maListe = initialiser_liste_a_niveaux(level);

        // Mesurer le temps pour la recherche dans le niveau 0
        startTimer();

        for (int i = 0; i < numSearches; i++) {
            searchLevel0(maListe, rand() % (1 << level));
        }
        stopTimer();
        char *time_lvl0 = getTimeAsString();

        // Mesurer le temps pour la recherche multi-niveaux
        startTimer();
        for (int i = 0; i < numSearches; i++) {
            searchFromTopLevel(maListe, rand() % (1 << level));
        }
        stopTimer();
        char *time_all_levels = getTimeAsString();

        // Afficher les résultats
        printf("%d %s %s\n", level, time_lvl0, time_all_levels);

        // Écrire les résultats dans le fichier de log
        fprintf(log_file,format,level,time_lvl0, time_all_levels);

    }

    fclose(log_file);
}