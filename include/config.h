#ifndef CONFIG_H
#define CONFIG_H

#include "xEngine.h"

extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;

extern const char WINDOW_TITLE[];
extern const char PATH_SAVEFILE[];

/// Vector2 {0, 0}
extern const xVector2 ZERO_POSITION;

/// Initialize window with width, height, title and set window icon.
void xInitWindow(void);

#endif