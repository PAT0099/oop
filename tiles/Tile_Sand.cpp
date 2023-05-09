#include "Tile_Sand.h"

Tile_Sand::Tile_Sand() {
    this->display_symbol = Helper::random(2) ? SAND_DISPLAY_SYMBOL_0 : SAND_DISPLAY_SYMBOL_1;
}

Tile_Sand::~Tile_Sand() {}

void Tile_Sand::display() {
    std::cout << FG_COLOR_YEL_BRI << BG_COLOR_YEL << this->display_symbol;
}

void Tile_Sand::tick() {
    if (!Helper::random(50)) {
        this->display_symbol = Helper::random(2) ? SAND_DISPLAY_SYMBOL_0 : SAND_DISPLAY_SYMBOL_1;
    }
}

char Tile_Sand::getType() {
    return TILE_TYPE_SAND;
}