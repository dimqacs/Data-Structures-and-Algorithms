#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "menu.h"

char **menuOptions = NULL;
unsigned int menuOptionCount = 0;

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
        *(menuOptions + i) = malloc(strlen(*(options + i)) + 1);

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

    unsigned int visibleIndex = 1;

    for (unsigned int i = 0; i < menuOptionCount; i++) {
        if (**(menuOptions + i) == '-') {
            printf("%s\n", *(menuOptions + i));
        } else {
            printf("%u. %s\n", visibleIndex, *(menuOptions + i));
            visibleIndex++;
        }
    }
}

void displayByeMessageAndExit() {
    printf("Bye!\n");
    exit(0);
}
