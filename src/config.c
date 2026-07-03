#include "config.h"

const int SCREEN_WIDTH = 1024;
const int SCREEN_HEIGHT = 832;

const char PATH_PLAYER_SHEET[] = "assets/player/player.png";
const char PATH_MAP[] = "assets/maps/map1.png";
const char WINDOW_TITLE[] = "Uprise - 2D RPG";
const char GAME_ICON[] = "assets/icons/icon_tree.png";
const char PATH_SAVEFILE[] = "../saves/save.xp";

const Vector2 ZERO_POSITION = {0, 0};

void xInitWindow()
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);
    Image WindowIcon = LoadImage(GAME_ICON);
    SetWindowIcon(WindowIcon);
}