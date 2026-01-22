#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "menu.h"

char **menuOptions = NULL;
unsigned int menuOptionCount = 0;

void clearTerminal() {
    #ifdef _WIN32
        system("clear");
    #else
        system("clear");
    #endif
}

void clearBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
    }
}

void handleNext(char message[]) {
    printf("%s \nPress Enter to continue...", message);
    clearBuffer();
    clearTerminal();
}

void setMenuOptions(const char *options[], const unsigned int optionCount) {
    menuOptions = calloc(optionCount, sizeof(char *));

    if (!menuOptions) {
        printf("Memory allocation failed. Can't set Menu, exiting the program.");
        exit(EXIT_FAILURE);
    }

    for (unsigned int i = 0; i < optionCount; i++) {
        *(menuOptions + i) = malloc(strlen(*(options + 1)) + 1);

        if (!*(menuOptions + i)) {
            printf("Memory allocation failed. Can't set Menu, exiting the program.");
            exit(EXIT_FAILURE);
        }

        strcpy(*(menuOptions + i), *(options + i));
    }

    menuOptionCount = optionCount;
}

void displayMenu() {
    printf("Options:\n");

    for (unsigned int i = 0; i < menuOptionCount; i++) {
        printf("%u. %s\n", i + 1, *(menuOptions + i));
    }

    printf("---------------------------------------------------------\n");
}

void displayByeMessageAndExit() {
    printf("Bye!\n");
    exit(0);
}
