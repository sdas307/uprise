#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"

typedef enum PLAYER_STATE
{
    playerIdle,
    playerWalking

} PLAYER_STATE;

typedef enum PLAYER_DIRECTION
{
    faceFront,
    faceBack,
    faceLeft,
    faceRight
    
} PLAYER_DIRECTION;

typedef struct Player
{
    Texture2D texture;

    Rectangle source;
    Rectangle dest;

    PLAYER_STATE state;
    PLAYER_DIRECTION direction;

    int speed;

    bool flip;

} Player;

void xInitPlayer(Player *player);

void xDrawPlayer(Player *player);

void xMovePlayer(Player *player);

void xUpdatePlayerAnimation(Player *player);

void xUpdatePlayer(Player *player);

void xUnloadPlayer(Player *player);


#endif