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
    sprintf(buffer, "[%g] %03d,%03d", _timer._msecs, (int)(_timer._msecs)/1000, (int)(_timer._msecs)%1000);

    // return the buffer
    return buffer;
}

void measureSearchTime(t_sk_list *list, int value, int numSearches) {
    clock_t start, end;
    double cpu_time_used;

    // Mesurer le temps pour la recherche dans le niveau 0
    start = clock();
    for (int i = 0; i < numSearches; i++) {
        searchLevel0(list, value);
    }
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Search in Level 0 Time: %f seconds\n", cpu_time_used);

    // Mesurer le temps pour la recherche à partir du niveau le plus haut
    start = clock();
    for (int i = 0; i < numSearches; i++) {
        searchFromTopLevel(list, value);
    }
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Search from Top Level Time: %f seconds\n", cpu_time_used);
}
