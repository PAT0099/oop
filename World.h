#pragma once
#include <unistd.h>
#include "tiles/Tile_Water.h"
#include "tiles/Tile_Sand.h"
#include "tiles/Tile_Grass.h"
#include "tiles/Tile_Tree.h"

//default sizes to nicely fit the terminal
#define WORLD_DEFAULT_WIDTH 78
#define WORLD_DEFAULT_HEIGHT 22

class World {
private:
    Tile** world_map;               //map of the world, 2d array of Tile*
    uint width;
    uint height;

    void initializeMap();           //initialize array
    void generateMap(int seed);     //generate a random map from a seed

    //helper functions for generation
    char generateGroup(uint x, uint y);
    void generateSmoothing();
    char generateCheckSmoothing(uint x, uint y);
    void generateTrees();

    bool setTileAt(uint x, uint y, Tile* tile); //return true if replacement was successful
    void display();                 //display map
    void tick();                    //tick once

public:
    // World constructors and deconstructor
    World();                        //default size, random seed
    World(int seed);                //default size, set seed
    World(uint w, uint h);          //set size, random seed
    World(uint w, uint h, int seed);//set size, set seed
    ~World();                       //free memory and stuff

    Tile* getTileAt(uint x, uint y);//returns tile at given location
    bool setTileAt(uint x, uint y, char type);

    void run();                     //main method that runs the simulation
};
