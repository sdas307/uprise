#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"
#include "xEngine.h"
#include "world.h"
#include "interactions.h"

typedef enum PlayerState
{
    PLAYER_IDLE,
    PLAYER_WALK,
    PLAYER_ATTACK,
    PLAYER_FISHING,

} PlayerState;

typedef enum PlayerEquipment
{
    EQUIP_NONE,
    EQUIP_LANTERN,
    EQUIP_TORCH,
    EQUIP_SWORD,
    EQUIP_BO,
    EQUIP_AXE,
    EQUIP_PICKAXE,
    EQUIP_HOE,
    EQUIP_WATERING_CAN,

    EQUIPMENTS_TOTAL
} PlayerEquipment;

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
    float runInterval;
    float walkInterval;

    float animationTimer;
    int currentFrame;
    int frameWidth;
    int frameHeight;

    PlayerState state;              /// Current player state.
    PlayerEquipment equipment;      /// Currently equipped item.

    PlayerDirection direction;      /// Current facing direction.

    InteractionTarget target;

    bool attackPressed;
    bool isRunning;

    int moveX;
    int moveY;

    int speed;          /// Player's movement speed.
    int walkSpeed;      /// Player's walking movement speed.
    int runSpeed;       /// Player's running movement speed.

} Player;

/// Initialize Player with default values.
void xInitPlayer(Player *player);

/// Update player values based on movement and animation logic.
void xUpdatePlayer(Player *player, World *world, xCamera2D gameCamera, float dt);             

/// Unload player object's texture from vram.
void xUnloadPlayer(Player *player);

/// Save player's serializable data.
bool xSavePlayer(const Player *player);

/// Load player data from file.
bool xLoadPlayer(Player *player);

#endif