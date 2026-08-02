#ifndef CAMERA_H
#define CAMERA_H

#include "xEngine.h"
#include "player.h"

void xInitCamera(xCamera2D *camera, const xGameObject *player);

void xUpdateCamera(xCamera2D *camera, const xGameObject *player);

void xCameraDebugLines(xCamera2D *camera);

#endif