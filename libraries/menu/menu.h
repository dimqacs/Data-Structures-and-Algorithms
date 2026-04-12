#pragma once

typedef void (display_t)(const void *element);

void clearTerminal();

void clearBuffer();

void handleNext(char message[]);

void setMenuOptions(const char *options[], unsigned int optionCount);

void displayMenu();

void displayByeMessageAndExit();
