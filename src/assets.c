#include "assets.h"
#include "config.h"

const char PATH_PLAYER_SHEET[] = "assets/player/player.png";

const char PATH_CHICKEN_SHEET[] = "assets/animals/chicken/chicken.png";
const char PATH_SHEEP_SHEET[] = "assets/animals/sheep/sheep.png";
const char PATH_PIG_SHEET[] = "assets/animals/pig/pig.png";
const char PATH_COW_SHEET[] = "assets/animals/cow/cow.png";

const char PATH_MAP[] = "assets/maps/map1.png";
const char PATH_TERRAIN[] = "assets/maps/terrain.png";
const char PATH_WORLD_OBJECTS[] = "assets/maps/world_objects_transparent.png";
const char PATH_SPRITE_SHEET[] = "assets/uprise_spritesheet/spritesheet.png";

/* ---------- Source Rectangles ----------*/

const xRectangle SPRITE_CHICKEN =
{
    64, 64, 64, 64
};

const xRectangle SPRITE_SHEEP = 
{
    64, 64, 64, 64
};

const xRectangle SPRITE_PIG = 
{
    64, 64, 64, 64
};

const xRectangle SPRITE_COW =
{
    20,
    22,
    64*2 - 30,
    64*2 - 42
};

const xRectangle SPRITE_HOUSE =
{
    64 * 15,
    62,
    64 * 5 - 40,
    64 * 7
};

const xRectangle SPRITE_LIGHT_POST =
{
    64 * 4 + 16,
    64 * 5,
    64 * 1 - 28,
    64 * 2
};

const xRectangle SPRITE_TREE_CUT =
{
    64 * 0,
    64 * 2,
    64,
    64
};

const xRectangle SPRITE_TREE_SMALL =
{
    64 * 5 + 15,
    64 * 5,
    64 * 2 - 34,
    64 * 2
};

const xRectangle SPRITE_TREE_LARGE =
{
    64 * 8 + 16,
    64 * 1 - 1,
    64 * 3 - 27,
    64 * 4
};

const xRectangle SPRITE_ROCK_SMALL = 
{
    64 * 1 + 8,
    64 * 2 + 20,
    64 - 24,
    64 - 36
};

const xRectangle SPRITE_ROCK_LARGE = 
{
    64 * 2,
    64 * 2 + 2,
    64 - 1,
    64 - 4
};

const xRectangle SPRITE_STONE_SMALL =
{
    64 * 2,
    64 * 3,
    64,
    64
};

const xRectangle SPRITE_STONE_MEDIUM =
{
    64 * 1,
    64 * 3,
    64,
    64
};

const xRectangle SPRITE_STONE_LARGE = 
{
    64 * 0,
    64 * 3,
    64,
    64
};