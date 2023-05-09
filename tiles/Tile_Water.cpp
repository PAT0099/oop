#include "Tile_Water.h"

Tile_Water::Tile_Water() {
    this->display_symbol = WATER_DISPLAY_SYMBOL_STILL;
    this->wave = Helper::random(WATER_STILL_MAX_WAIT);
}

Tile_Water::~Tile_Water() {}

void Tile_Water::display() {
    std::cout << FG_COLOR_CYA_BRI << BG_COLOR_BLU << this->display_symbol;
}

void Tile_Water::tick() {
    this->wave -= 1;
    if (this->wave == WATER_SPLASH_LENGTH) { //make water splashy
        this->display_symbol = WATER_DISPLAY_SYMBOL_SPLASH;
    }
    else if (this->wave <= 0) { //make water still
        this->wave = (rand() % WATER_STILL_MAX_WAIT) + WATER_STILL_WAIT;
        this->display_symbol = WATER_DISPLAY_SYMBOL_STILL;
    }
}

char Tile_Water::getType() {
    return TILE_TYPE_WATER;
}