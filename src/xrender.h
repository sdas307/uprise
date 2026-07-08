#ifndef X_RENDER_H
#define X_RENDER_H

#include "xEngine.h"
#include "player.h"
#include "map.h"

void xRenderScene(xGameObject *objects, int count);

void xRenderTerrain(Map *map);

void xRenderMapObjects(Map *map);

void xRenderObject(xGameObject *object);

void xRenderPlayer(Player *player);

#endif