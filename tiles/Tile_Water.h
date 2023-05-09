#pragma once
#include "Tile.h"

#define WATER_STILL_MAX_WAIT 20
#define WATER_STILL_WAIT 10
#define WATER_SPLASH_LENGTH 2
#define WATER_DISPLAY_SYMBOL_STILL ' '
#define WATER_DISPLAY_SYMBOL_SPLASH '~'

class Tile_Water : public Tile {
private:
    char wave = 0;
    
public:
    Tile_Water();
    ~Tile_Water();

    void display();
    void tick();
    char getType();
};
