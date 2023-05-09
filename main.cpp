#include "World.h"

int main() {
    World* world = new World(130, 41);
    world->run();
    delete world;
    return 0;
}
