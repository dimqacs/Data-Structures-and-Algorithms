#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char **menuOptions = NULL;
static unsigned int menuOptionCount = 0;

static void clearTerminal() {
    system("clear");
}

static void clearBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
    }
}

static void handleNext(char message[]) {
    clearBuffer();
    printf("%s \nPress Enter to continue...", message);
    clearBuffer();
    clearTerminal();
}

static void setMenuOptions(const char *options[], const unsigned int optionCount) {
    menuOptions = calloc(optionCount, sizeof(char *));

    if (!menuOptions) {
        printf("Memory allocation failed. Can't set Menu, exiting the program.");
        exit(0);
    }

    for (unsigned int i = 0; i < optionCount; i++) {
        *(menuOptions + i) = malloc(strlen(*(options + 1)) + 1); // NOLINT

        if (!*(menuOptions + i)) {
            printf("Memory allocation failed. Can't set Menu, exiting the program.");
            exit(0);
        }

        strcpy(*(menuOptions + i), *(options + i));
    }

    menuOptionCount = optionCount;
}

static void displayMenu() {
    printf("Options:\n");

    for (unsigned int i = 0; i < menuOptionCount; i++) {
        printf("%u. %s\n", i + 1, *(menuOptions + i));
    }

    printf("---------------------------------------------------------\n");
}

static void displayByeMessageAndExit() {
    printf("Bye!\n");
    exit(0);
}