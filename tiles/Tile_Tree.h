#pragma once
#include "Tile.h"

#define TREE_GROW_AGE 10
#define TREE_MAX_AGE 50
#define TREE_PROPAGATION_CHANCE 10
#define TREE_DISPLAY_SYMBOL_0 't'
#define TREE_DISPLAY_SYMBOL_1 'T'

class World;

class Tile_Tree : public Tile {
private:
    int age;
    uint x;
    uint y;
    World* w;

public:
    Tile_Tree(World* w, uint x, uint y);
    Tile_Tree(World* w, uint x, uint y, int age);
    ~Tile_Tree();

    void display();
    void tick();
    char getType();
    void propagate();
};
