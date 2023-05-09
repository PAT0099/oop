#pragma once
#include "Tile.h"

#define SAND_DISPLAY_SYMBOL_0 '.'
#define SAND_DISPLAY_SYMBOL_1 ','

class Tile_Sand : public Tile {
// no additional properties
public:
    Tile_Sand();
    ~Tile_Sand();

    void display();
    void tick();
    char getType();
};
