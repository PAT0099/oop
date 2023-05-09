#pragma once
#include <iostream>
#include "../Helper.h"

//reset colors
#define COLOR_RESET "\x1B[0m"

//foreground colors
#define FG_COLOR_BLK "\x1B[30m"
#define FG_COLOR_RED "\x1B[31m"
#define FG_COLOR_GRN "\x1B[32m"
#define FG_COLOR_YEL "\x1B[33m"
#define FG_COLOR_BLU "\x1B[34m"
#define FG_COLOR_MAG "\x1B[35m"
#define FG_COLOR_CYA "\x1B[36m"
#define FG_COLOR_WHT "\x1B[37m"
#define FG_COLOR_BLK_BRI "\x1B[90m"
#define FG_COLOR_RED_BRI "\x1B[91m"
#define FG_COLOR_GRN_BRI "\x1B[92m"
#define FG_COLOR_YEL_BRI "\x1B[93m"
#define FG_COLOR_BLU_BRI "\x1B[94m"
#define FG_COLOR_MAG_BRI "\x1B[95m"
#define FG_COLOR_CYA_BRI "\x1B[96m"
#define FG_COLOR_WHT_BRI "\x1B[97m"

//background colors
#define BG_COLOR_BLK "\x1B[40m"
#define BG_COLOR_RED "\x1B[41m"
#define BG_COLOR_GRN "\x1B[42m"
#define BG_COLOR_YEL "\x1B[43m"
#define BG_COLOR_BLU "\x1B[44m"
#define BG_COLOR_MAG "\x1B[45m"
#define BG_COLOR_CYA "\x1B[46m"
#define BG_COLOR_WHT "\x1B[47m"
#define BG_COLOR_BLK_BRI "\x1B[100m"
#define BG_COLOR_RED_BRI "\x1B[101m"
#define BG_COLOR_GRN_BRI "\x1B[102m"
#define BG_COLOR_YEL_BRI "\x1B[103m"
#define BG_COLOR_BLU_BRI "\x1B[104m"
#define BG_COLOR_MAG_BRI "\x1B[105m"
#define BG_COLOR_CYA_BRI "\x1B[106m"
#define BG_COLOR_WHT_BRI "\x1B[107m"

//tile types
#define TILE_TYPE_WATER 1
#define TILE_TYPE_SAND 2
#define TILE_TYPE_GRASS 3
#define TILE_TYPE_TREE 4

class Tile {
protected:
    char display_symbol;

public:
    virtual ~Tile() = default;
    virtual void display() = 0;
    virtual void tick() = 0;
    virtual char getType() = 0;
};