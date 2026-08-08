#include "assets.h"
#include "config.h"
#include <string.h>

const char PATH_PLAYER_SHEET[] = "assets/old_assets/player/player.png";

const char PATH_CHICKEN_SHEET[] = "assets/old_assets/animals/chicken/chicken.png";
const char PATH_SHEEP_SHEET[] = "assets/old_assets/animals/sheep/sheep.png";
const char PATH_PIG_SHEET[] = "assets/old_assets/animals/pig/pig.png";
const char PATH_COW_SHEET[] = "assets/old_assets/animals/cow/cow.png";

const char PATH_MAP[] = "assets/old_assets/maps/map1.png";
const char PATH_BASE[] = "assets/old_assets/maps/map_base.png";
const char PATH_FOREST[] = "assets/old_assets/maps/map_forest.png";
const char PATH_WORLD_OBJECTS[] = "assets/old_assets/maps/world_objects_transparent.png";
const char PATH_SPRITE_SHEET[] = "assets/old_assets/uprise_spritesheet/spritesheet.png";

const char PATH_START_BASE[] = "assets/new/world_maps/starting_base.png";

const char *PATH_SPRITESHEETS[] = 
{
    "assets/new/spritesheets/structures/house_wood.png",
    "assets/new/spritesheets/structures/fence_posts.png",
    "assets/new/spritesheets/structures/bridge_walls.png",

    "assets/new/spritesheets/nature/trees.png",
    "assets/new/spritesheets/nature/grasslands.png",
    "assets/new/spritesheets/nature/grass_wildflowers.png",
    "assets/new/spritesheets/nature/crops_fruits.png",
    "assets/new/spritesheets/nature/flower_mushrooms.png",
    "assets/new/spritesheets/nature/cliffs.png",
    "assets/new/spritesheets/nature/water.png",
    "assets/new/spritesheets/nature/waterfall.png",

    "assets/new/spritesheets/cave/cave.png",
    "assets/new/spritesheets/weather/weather_effects.png"
};
const int path_spritesheets_size = ARRAY_COUNT(PATH_SPRITESHEETS);