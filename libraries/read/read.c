#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "read.h"

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

unsigned int readUnsignedInt(const char *prompt, unsigned int *out) {
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
        return 1;
    }
}

