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
