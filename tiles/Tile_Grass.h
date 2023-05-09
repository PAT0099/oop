#pragma once
#include "Tile.h"

class Tile_Grass : public Tile {
private:
    char grass_display[3] = {'/', '|', '\\'};
    int grass_chances[3] = {50, 35, 15};

public:
    Tile_Grass();
    ~Tile_Grass();

    void display();
    void tick();
    char getType();
};
