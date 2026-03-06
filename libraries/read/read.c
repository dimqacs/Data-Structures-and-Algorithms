#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "read.h"

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

void handleFailureExit(const char *reason) {
    printf("%s", reason);
    exit(EXIT_FAILURE);
}

int readInt(const char *prompt, int *out) {
    char buffer[64];
    char *end;

    while (true) {
        printf("%s", prompt);

        if (!fgets(buffer, sizeof(buffer), stdin)) {
            handleFailureExit("Error: unable to read input. Exiting...\n");
        }

        const long value = strtol(buffer, &end, 10);

        if (end == buffer || *end != '\n') {
            printf("Invalid Integer Provided. Try again.\n");
            continue;
        }

        *out = (int) value;
        return 1;
    }
}

void readUnsignedInt(const char *prompt, unsigned int *out) {
    char buffer[64];
    char *end;

    while (true) {
        printf("%s", prompt);

        if (!fgets(buffer, sizeof(buffer), stdin)) {
            handleFailureExit("Error: unable to read input. Exiting...\n");
        }

        const long value = strtol(buffer, &end, 10);

        if (end == buffer || *end != '\n' || value < 0) {
            printf("Invalid Unsigned Integer Provided. Try again.\n");
            continue;
        }

        *out = (int) value;
        break;
    }
}

void readUnsignedFloat(const char *prompt, float *out) {
    char buffer[64];
    char *end;

    while (true) {
        printf("%s", prompt);

        if (!fgets(buffer, sizeof(buffer), stdin)) {
            handleFailureExit("Error: unable to read input. Exiting...\n");
        }

        buffer[strcspn(buffer, "\n")] = 0;

        const float value = strtof(buffer, &end);

        if (end == buffer || *end != '\0' || value < 0) {
            printf("Invalid Unsigned Float Provided. Try again.\n");
            continue;
        }

        *out = value;
        break;
    }
}
