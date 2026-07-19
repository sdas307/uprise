#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"
#include "xEngine.h"
#include "world.h"

typedef enum PlayerState
{
    PLAYER_IDLE,
    PLAYER_WALK,
    PLAYER_ATTACK

} PlayerState;

typedef enum PlayerDirection
{
    PLAYER_FACE_FRONT,
    PLAYER_FACE_BACK,
    PLAYER_FACE_LEFT,
    PLAYER_FACE_RIGHT
    
} PlayerDirection;

/// Player object configured with basic components.
typedef struct Player
{
    xGameObject gameObject;

    float interval;             /// Animation interval.

    float animationTimer;
    int currentFrame;
    int frameWidth;
    int frameHeight;

    PlayerState state;         /// Current player state.

    PlayerDirection direction; /// Current facing direction.

    bool attackPressed;

    int moveX;
    int moveY;

    int speed;      /// Player's movement speed.

} Player;

/// Initialize Player with default values.
void xInitPlayer(Player *player);

/// Update player values based on movement and animation logic.
void xUpdatePlayer(Player *player, World *world);             

/// Unload player object's texture from vram.
void xUnloadPlayer(Player *player);

/// Save player's serializable data.
bool xSavePlayer(const Player *player);

/// Load player data from file.
bool xLoadPlayer(Player *player);

#endif