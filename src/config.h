#ifndef CONFIG_H
#define CONFIG_H

#include "raylib.h"

extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;

extern const char PATH_PLAYER_SHEET[];
extern const char PATH_MAP[];
extern const char WINDOW_TITLE[];
extern const char PATH_SAVEFILE[];

extern const Vector2 ZERO_POSITION;

void xInitWindow();

#endif