#ifndef CONFIG_H
#define CONFIG_H

#include "xEngine.h"

extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;

extern const char WINDOW_TITLE[];
extern const char PATH_SAVEFILE[];

extern const xVector2 ZERO_POSITION;

void xInitWindow(void);

#endif