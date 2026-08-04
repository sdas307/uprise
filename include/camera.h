#ifndef CAMERA_H
#define CAMERA_H

#include "xEngine.h"
#include "player.h"

/// Boundary for the camera to remian within.
typedef struct CameraBoundary
{
    int up;
    int down;
    int left;
    int right;

} CameraBoundary;

/// Camera2D with more features.
typedef struct xGameCamera
{
    xCamera2D camera;               /// raylib's camera2d.

    CameraBoundary bounds;          /// Camera boundary.

} xGameCamera;

/** Initialize camera to follow an object with an offset.
 * @param camera Camera to initialize.
 * @param object Object to follow.
 */
void xInitCamera(xGameCamera *gameCamera, const xGameObject *object);

/** Update camera every frame.
 * @param camera Camera to update.
 * @param object Object to follow.
 */
void xUpdateCamera(xGameCamera *gameCamera, const xGameObject *object);

/// Draw debug lines to show the point the camera is following.
void xCameraDebugLines(xCamera2D *camera);

#endif