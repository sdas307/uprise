#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"

typedef enum PlayerState
{
    PLAYER_IDLE,
    PLAYER_WALKING

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
    
    Texture2D spriteSheet;      /// Player spritesheet.
    float interval;             /// Animation interval.

    Rectangle source;           /// Sprite Sheet rectangle.
    Rectangle dest;             /// Screen rectangle.

    PlayerState state;         /// Current player state.

    PlayerDirection direction; /// Current facing direction.

    int speed;      /// Player's movement speed.

    bool flip;      /// Flip sprite horizontally when facing left.

} Player;

/// Initialize Player with default values.
void xInitPlayer(Player *player);

/// Draw player at its current position.
void xDrawPlayer(Player *player);

/// Move player based on user input.
void xMovePlayer(Player *player);

/// Update player sprites to show animation.
void xUpdatePlayerAnimation(Player *player);

/// Update player values based on movement and animation logic.
void xUpdatePlayer(Player *player);             

/// Unload player object's texture from vram.
void xUnloadPlayer(Player *player);

/// Save player's serializable data.
bool xSavePlayer(const Player *player);

/// Load player data from file.
bool xLoadPlayer(Player *player);

#endif