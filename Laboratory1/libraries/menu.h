#pragma once
#include <stdio.h>
#include <stdlib.h>

static void clearTerminal() {
    system("clear");
}

static void displayMenu() {
    printf("Options:\n");
    printf("1. Display Array\n");
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
    while ((c = getchar()) != '\n' && c != EOF) {
    }
}

static void handleError(char errorMessage[]) {
    clearBuffer();
    printf("%s \nPress Enter...", errorMessage);
    getchar();
    clearTerminal();
}

static void handleNormalCase() {
    printf("Press Enter to continue...");
    getchar();
    clearTerminal();
}
