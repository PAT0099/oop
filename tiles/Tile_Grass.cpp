#include "Tile_Grass.h"

Tile_Grass::Tile_Grass() {
    this->display_symbol = '|';
}

Tile_Grass::~Tile_Grass() { }

void Tile_Grass::display() {
    std::cout << FG_COLOR_GRN_BRI << BG_COLOR_GRN << this->display_symbol;
}

void Tile_Grass::tick() {
    this->display_symbol = this->grass_display[Helper::choose(3, this->grass_chances)];
}

char Tile_Grass::getType() {
    return TILE_TYPE_GRASS;
}