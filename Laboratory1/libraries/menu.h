#pragma once
#include <stdio.h>
#include <stdlib.h>

static void clearTerminal() {
    printf("\e[1;1H\e[2J");
}

static void handleNormalCase() {
    printf("If you want to continue press Enter...");
    getchar();
    clearTerminal();
}

static void displayArray(const int count, const int* array) {
    if (count == 0) {
        printf("The array is empty, try introducing values first. \n");
        handleNormalCase();
    }

    for (int i = 0; i < count; i++) {
        printf("%d ", array[i]);
    }
}

static void displayMenu() {
    printf("Options:\n");
    printf("1. Show Array\n");
    printf("2. Fill Array Manually\n");
    printf("3. Fill Array Randomly\n");
    printf("4. Sort Array\n");
    printf("5. Free Space & Exit\n");
    printf("---------------------------------------------------------\n");
}

static void displayByeMessageAndExit() {
    printf("Bye!\n");
    exit(0);
}

static void clearBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

static void handleError(char errorMessage[]) {
    clearBuffer();
    printf("%s \nPress Enter...", errorMessage);
    getchar();
    clearTerminal();
}

static int* fillArrayManually() {
    // int* array = malloc(*size * sizeof(int));
    //
    // return array;
}