#include <time.h>
#include <bits/time.h>

#include "math.h"

bool isPrime(const int value) {
    if (value < 2) {
        return false;
    }

    for (int index = 2; index * index <= value; index++) {
        if (value % index == 0) {
            return false;
        }
    }

    return true;
}

int getRandomNumber(const int min, const int max) {
    struct timespec ts;
    clock_gettime(CLOCK_REALTIME, &ts);
    long milliseconds = ts.tv_nsec + ts.tv_sec * 1000000;

    // Linear Congruential Generator (LCG) https://en.wikipedia.org/wiki/Linear_congruential_generator
    milliseconds = (milliseconds * 214013 + 2531011) % 2147483648;

    const int range = max - min + 1;

    return (int) (milliseconds % range + range) % range + min;
}