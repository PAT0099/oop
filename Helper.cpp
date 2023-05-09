#include "Helper.h"

void Helper::setSeed(int seed) {
    srand(seed);
}

int Helper::random() {
    return rand();
}

int Helper::random(int mod) {
    return rand() % mod;
}

int Helper::random(int min, int max) {
    return min > max ? 0 : (rand() % (max - min)) + min;
}

int Helper::choose(int count, int values[]) {
    int sum = 0;
    for (int i = 0; i < count; i++) {
        sum += values[i];
    }
    int val = Helper::random(sum);
    sum = 0;
    for (int i = 0; i < count; i++) {
        sum += values[i];
        if (val < sum) {
            return i;
        }
    }
    return 0; //this line shouldn't run
}