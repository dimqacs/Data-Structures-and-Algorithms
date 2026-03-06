#pragma once

void clearTerminal();

void clearBuffer();

void handleFailureExit(const char *reason);

int readInt(const char *prompt, int *out);

void readUnsignedInt(const char *prompt, unsigned int *out);

void readUnsignedFloat(const char *prompt, float *out);
