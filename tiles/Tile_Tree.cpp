#include "Tile_Tree.h"
#include "../World.h"

Tile_Tree::Tile_Tree(World* w, uint x, uint y) {
    this->display_symbol = TREE_DISPLAY_SYMBOL_0;
    this->w = w;
    this->x = x;
    this->y = y;
    this->age = 0;
}

Tile_Tree::Tile_Tree(World* w, uint x, uint y, int age) {
    this->display_symbol = TREE_DISPLAY_SYMBOL_0;
    this->w = w;
    this->x = x;
    this->y = y;
    this->age = age;
    if (this->age > 10) {
        this->display_symbol = TREE_DISPLAY_SYMBOL_1;
    }
}

Tile_Tree::~Tile_Tree() {}

void Tile_Tree::display() {
    std::cout << FG_COLOR_RED << BG_COLOR_GRN << this->display_symbol;
}

void Tile_Tree::tick() {
    if (this->age > TREE_MAX_AGE) {
        //I have no idea if this is the correct way to do this but it doesn't leak memory
        w->setTileAt(this->x, this->y, 3); //this deletes the tree
        return;
    } else if (this->age > TREE_GROW_AGE) {
        if (!Helper::random(TREE_PROPAGATION_CHANCE)) {
            this->propagate();
        }
    } else if (this->age == TREE_GROW_AGE) {
        this->display_symbol = TREE_DISPLAY_SYMBOL_1;
    }
    this->age += 1;
}

char Tile_Tree::getType() {
    return TILE_TYPE_TREE;
}

// Choose a random direction and try to place a tree there
void Tile_Tree::propagate() {
    char choice = Helper::random(8);
    uint new_x = this->x;
    uint new_y = this->y;
    switch (choice) {
        case 0: new_x -= 1; new_y -= 1; break;
        case 1:             new_y -= 1; break;
        case 2: new_x += 1; new_y -= 1; break;
        case 3: new_x -= 1;             break;
        case 4: new_x += 1;             break;
        case 5: new_x -= 1; new_y += 1; break;
        case 6:             new_y += 1; break;
        case 7: new_x += 1; new_y += 1; break;
        default: break;
    }
    if (w->getTileAt(new_x, new_y) == nullptr) {
        return;
    }
    if (w->getTileAt(new_x, new_y)->getType() == TILE_TYPE_GRASS) {
        w->setTileAt(new_x, new_y, TILE_TYPE_TREE);
    }
}