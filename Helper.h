#pragma once
#include <stdlib.h>

#define uint unsigned int

// Helper class for randomness
class Helper {
public:
    static void setSeed(int seed);
    static int random();
    static int random(int mod);
    static int random(int min, int max);
    static int choose(int count, int values[]);
};
