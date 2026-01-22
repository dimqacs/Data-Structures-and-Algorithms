#pragma once

void clearTerminal();

void clearBuffer();

void handleNext(char message[]);

void setMenuOptions(const char *options[], const unsigned int optionCount);

void displayMenu();

void displayByeMessageAndExit();
