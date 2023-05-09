#include "World.h"

// Generate a world with default settings and random seed
World::World() {
    this->width = WORLD_DEFAULT_WIDTH;
    this->height = WORLD_DEFAULT_HEIGHT;
    this->initializeMap();

    Helper::setSeed(time(NULL));
    this->generateMap(Helper::random());
}

// Generate a world with default settings and set seed
World::World(int seed) {
    this->width = WORLD_DEFAULT_WIDTH;
    this->height = WORLD_DEFAULT_HEIGHT;
    this->initializeMap();

    Helper::setSeed(seed);
    this->generateMap(Helper::random());
}

// Generate a world with set width and height, but random seed
World::World(uint w, uint h) {
    this->width = w;
    this->height = h;
    this->initializeMap();

    Helper::setSeed(time(NULL));
    this->generateMap(Helper::random());
}

//Generate a world with set width, height and seed
World::World(uint w, uint h, int seed) {
    this->width = w;
    this->height = h;
    this->initializeMap();

    Helper::setSeed(seed);
    this->generateMap(Helper::random());
}

// Safely delete world
World::~World() {
    uint size = width * height;
    for (uint i = 0; i < size; i++) {
        delete world_map[i];
    }
    delete[] world_map;
}

// Returns pointer to tile at location [x, y] or nullptr if out of bounds.
Tile* World::getTileAt(uint x, uint y) {
    if (x < 0 || x >= this->width || y < 0 || y >= this->height) {
        return nullptr;
    }
    return this->world_map[y * this->width + x];
}

// Sets tile at location [x, y] to desired type
// Return true if replacement went well
bool World::setTileAt(uint x, uint y, Tile* tile) {
    Tile* old_tile = this->getTileAt(x, y);
    if (old_tile == nullptr || tile->getType() == old_tile->getType()) {
        delete tile;
        return false;
    }
    delete old_tile;
    this->world_map[y * this->width + x] = tile;
    return true;
}

// Same as above, but only type is needed
bool World::setTileAt(uint x, uint y, char type) {
    Tile* new_tile;
    switch (type) {
        case TILE_TYPE_WATER: new_tile = new Tile_Water(); break;
        case TILE_TYPE_SAND: new_tile = new Tile_Sand(); break;
        case TILE_TYPE_GRASS: new_tile = new Tile_Grass(); break;
        case TILE_TYPE_TREE: new_tile = new Tile_Tree(this, x, y); break;
        default: return false;
    }
    return this->setTileAt(x, y, new_tile);
}

// Initialize array, set all tiles to Water
void World::initializeMap() {
    uint size = this->width * this->height;
    this->world_map = new Tile* [size];
    for (int i = 0; i < size; i++) {
        this->world_map[i] = new Tile_Water();
    }
}

// Generate grass tiles, smoothe with sand, add trees
void World::generateMap(int seed) {
    int grass_total = (this->width * this->height) / 6;
    int grass_count = 0;
    int fails_allowed = (this->width * this->height) / 100;

    uint new_x = Helper::random(this->width);
    uint new_y = Helper::random(this->height);
    while (grass_count < grass_total && fails_allowed) {
        //generate a group of 5
        int grass_generated = this->generateGroup(new_x, new_y);

        if (grass_generated == 0) { //if no new tiles got generated
            new_x = Helper::random(this->width);
            new_y = Helper::random(this->height);
            fails_allowed -= 1;
        } else { //continue generating on current island
            char loc = Helper::random(8);
            new_x += (loc & 0b1 ? +1 : -1) * (loc & 0b10 ? 2 : 1);
            new_y += (loc & 0b100 ? +1 : -1) * (loc & 0b10 ? 1 : 2);
            grass_count += grass_generated;
        }
    }
    this->generateSmoothing();
    this->generateTrees();
}

// Helper function, generates a single group of 5 grass
char World::generateGroup(uint x, uint y) {
    char gen = 0;
    gen += this->setTileAt(x, y, new Tile_Grass()) ? 1 : 0;
    gen += this->setTileAt(x - 1, y, new Tile_Grass()) ? 1 : 0;
    gen += this->setTileAt(x + 1, y, new Tile_Grass()) ? 1 : 0;
    gen += this->setTileAt(x, y - 1, new Tile_Grass()) ? 1 : 0;
    gen += this->setTileAt(x, y + 1, new Tile_Grass()) ? 1 : 0;
    return gen;
}

// Smoothes out the terrain
void World::generateSmoothing() {
    int row = 0;
    while (row < this->height) {
        bool smoothed = false;
        for (uint col = 0; col < this->width; col++) {
            char smoothType = this->generateCheckSmoothing(col, row);
            if (smoothType == TILE_TYPE_GRASS) {
                this->setTileAt(col, row, new Tile_Grass());
                smoothed = true;
            } else if (smoothType == TILE_TYPE_SAND) {
                this->setTileAt(col, row, new Tile_Sand());
                smoothed = true;
            }
        }
        
        if (smoothed && row > 0) {
            row -= 1;
        } else {
            row += 1;
        }
    }
}

// Helper function to smoothe out terrain
char World::generateCheckSmoothing(uint x, uint y) {
    //get out if it's not suitable for smoothing
    char self_type = this->getTileAt(x, y)->getType();
    if (self_type == TILE_TYPE_GRASS) {
        return 0;
    }

    //get a 3x3 area around the tile
    Tile* neighbors[8] = {
        this->getTileAt(x-1, y-1), this->getTileAt(x, y-1), this->getTileAt(x+1, y-1),
        this->getTileAt(x-1, y), this->getTileAt(x+1, y),
        this->getTileAt(x-1, y+1), this->getTileAt(x, y+1), this->getTileAt(x+1, y+1)
    };

    //check for grass and also sand
    int grass_count = 0;
    int sand_count = 0;
    for (int i = 0; i < 8; i++) {
        if (neighbors[i] == nullptr) {
            continue;
        }
        if (neighbors[i]->getType() == TILE_TYPE_GRASS) {
            grass_count += 1;
        } else if (neighbors[i]->getType() == TILE_TYPE_SAND) {
            sand_count += 1;
        }
    }
    if (grass_count > 4) {
        return TILE_TYPE_GRASS; //if there's a lot of grass around, place grass
    } else if (self_type != TILE_TYPE_SAND && (grass_count > 0 || sand_count > 4)) {
        return TILE_TYPE_SAND; //if there's grass or some sand around, place sand
    }
    return 0;
}

// Place some trees in the world
void World::generateTrees() {
    for (uint row = 0; row < this->height; row++) {
        for (uint col = 0; col < this->width; col++) {
            if (this->getTileAt(col, row)->getType() == TILE_TYPE_GRASS && !Helper::random(20)) {
                this->setTileAt(col, row, new Tile_Tree(this, col, row, Helper::random(TREE_MAX_AGE)));
            }
        }
    }
}

// Display world
void World::display() {
    //print top border
    std::cout << std::endl << FG_COLOR_MAG_BRI << BG_COLOR_MAG;
    for (int col = 0; col < this->width + 2; col++) {
        std::cout << '#';
    }

    //print map
    std::cout << COLOR_RESET << std::endl;
    for (uint row = 0; row < this->height; row++) {
        std::cout << FG_COLOR_MAG_BRI << BG_COLOR_MAG << '#';
        for (uint col = 0; col < this->width; col++) {
            this->getTileAt(col, row)->display();
        }
        std::cout << FG_COLOR_MAG_BRI << BG_COLOR_MAG << '#' << COLOR_RESET << std::endl;
    }

    //print bottom border
    std::cout << FG_COLOR_MAG_BRI << BG_COLOR_MAG;
    for (int col = 0; col < this->width + 2; col++) {
        std::cout << '#';
    }
    std::cout << COLOR_RESET << std::flush;
}

// Tick world
void World::tick() {
    for (uint row = 0; row < this->height; row++) {
        for (uint col = 0; col < this->width; col++) {
            this->getTileAt(col, row)->tick();
        }
    }
    
}

// Run simulation
void World::run() {
    for (int i = 0; i < 10; i++) {
        this->tick();
        this->display();
        sleep(1);
    }
    std::cout << std::endl << "The world finished ticking :)" << std::endl;
}
