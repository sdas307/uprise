#include "player.h"
#include "config.h"
#include "assets.h"

#include "raymath.h"
#include <stdio.h>

/* ---------- Signatures ---------- */

/// Check collisions between player and world objects
static bool xCheckCollision(World *world, xRectangle collider);

/// Handle user input (keyboard/mouse).
static void xReadPlayerInput(Player *player);

/// Update player state based on user input.
static void xUpdatePlayerState(Player *player);

/// Move player based on user input.
static void xMovePlayer(Player *player, World *world);

/// Update player sprites to show animation.
static void xUpdatePlayerAnimation(Player *player);

/// Get the number of frames for animation.
static int xGetAnimationLength(PlayerState state);

/// Get the row index of the animation in question.
static int xGetAnimationRow(PlayerState state, PlayerDirection direction);


/* ---------- Implementation ---------- */

typedef struct PlayerConfig
{
    int x;      // Player spawn x.
    int y;      // Player spawn y.
    int speed;  // Player movement speed.

} PlayerConfig;

typedef struct PlayerSave
{
    Rectangle dest;

    int speed;

    PlayerState state;
    PlayerDirection direction;

    bool flip;

} PlayerSave;

/** Player Object is made in main file,
 * here we simply define all funcitons and
 * possible opertaions on Player.
 */

bool LoadPlayerConfig(PlayerConfig *config)
{
    FILE *file = fopen("config/player.cfg", "r");

    if (file == NULL)
    {
        perror("Failed to open player.cfg");
        return false;
    }

    // If any of the operations fail, return false.
    /* The leading space before each string is an idomatic way
    to tell fscanf to ignore all whitespace (\n, \t, etc.) */
    if (fscanf(file, " x = %d", &config->x) != 1 ||
        fscanf(file, " y = %d", &config->y) != 1 ||
        fscanf(file, " speed = %d", &config->speed) != 1)
    {
        fclose(file);
        return false;
    }

    // If nothing fails, close file and return true.
    fclose(file);
    return true;
}

void xInitPlayer(Player *player)
{
    PlayerConfig config =
    {
        .x = 0,
        .y = 200,
        .speed = 3
    };

    if (!LoadPlayerConfig(&config))
    {
        printf("\n\n");
        printf("Using default player configuration: Loading failed.");
        printf("\n\n");
    }

    player->gameObject.texture = LoadTexture(PATH_PLAYER_SHEET);
    SetTextureFilter(player->gameObject.texture, TEXTURE_FILTER_POINT);

    player->interval = 0.10f;

    player->animationTimer = 0.0f;
    player->currentFrame = 0;

    player->frameWidth = 32;
    player->frameHeight = 32;

    player->gameObject.source = (xRectangle) {0, 0, player->frameWidth, player->frameHeight};
    player->gameObject.dest = (xRectangle) {config.x, config.y, player->frameWidth * 4, player->frameHeight * 4};

    player->gameObject.type = OBJECT_PLAYER;

    player->gameObject.active = true;

    player->gameObject.collider = (xRectangle)
    {
        player->gameObject.dest.x + 44,
        player->gameObject.dest.y + 80,
        38,
        12,
    };

    player->gameObject.depth = player->gameObject.collider.y + player->gameObject.collider.height;

    player->speed = config.speed;
    // printf("speed = %d", config.speed);
    
    player->state = PLAYER_IDLE;
    player->direction = PLAYER_FACE_FRONT;
    player->gameObject.flip = false;
}

void xUpdatePlayer(Player *player, World *world)
{
    xReadPlayerInput(player);
    xUpdatePlayerState(player);
    xMovePlayer(player, world);
    xUpdatePlayerAnimation(player);
    DrawRectangleLinesEx(player->gameObject.dest, 1.0f, RED);
}

void xUnloadPlayer(Player *player)
{
    UnloadTexture(player->gameObject.texture);
}

static void xReadPlayerInput(Player *player)
{
    player->moveX = 0;
    player->moveY = 0;

    if (IsKeyDown(KEY_W))
        player->moveY--;

    if (IsKeyDown(KEY_S))
        player->moveY++;

    if (IsKeyDown(KEY_A))
        player->moveX--;

    if (IsKeyDown(KEY_D))
        player->moveX++;

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        player->attackPressed = true;

}

static void xUpdatePlayerState(Player *player)
{
    if (player->state == PLAYER_ATTACK)
    {
        return;
    }

    if (player->attackPressed)
    {
        player->state = PLAYER_ATTACK;
        player->currentFrame = 0;
        player->animationTimer = 0.0f;

        player->attackPressed = false;

        return;
    }

    if ((player->moveX != 0) || (player->moveY != 0))
    {
        player->state = PLAYER_WALK;
    }
    else
    {
        player->state = PLAYER_IDLE;
    }
}

static void xMovePlayer(Player *player, World *world)
{
    // No movement while attacking.
    if (player->state == PLAYER_ATTACK)
        return;

    int dx = player->moveX;
    int dy = player->moveY;

    // No movement requested.
    if ((dx == 0) && (dy == 0))
        return;

    if (dy < 0)
    {
        player->direction = PLAYER_FACE_BACK;
    }
    else if (dy > 0)
    {
        player->direction = PLAYER_FACE_FRONT;
    }

    if (dx < 0)
    {
        player->direction = PLAYER_FACE_LEFT;
        player->gameObject.flip = true;
    }
    else if (dx > 0)
    {
        player->direction = PLAYER_FACE_RIGHT;
        player->gameObject.flip = false;
    }

    // Create a movement vector from player input.
    // Essentially copy values every frame (only 2 (int) floats: x, y)
    xVector2 movement = {dx, dy};

    if (Vector2Length(movement) == 0)
        return;

    // Normalize diagonal movement to maintain a constant speed.
    movement = Vector2Normalize(movement);

    xRectangle nextCollider = player->gameObject.collider;
    nextCollider.x += movement.x * player->speed;
    nextCollider.y += movement.y * player->speed;

    if (!xCheckCollision(world, nextCollider))
    {
        player->gameObject.dest.x += movement.x * player->speed;
        player->gameObject.dest.y += movement.y * player->speed;

        player->gameObject.collider = nextCollider;

        player->gameObject.depth = player->gameObject.collider.y + player->gameObject.collider.height;
    }
}

static bool xCheckCollision(World *world, xRectangle collider)
{
    for (int i=0; i < world->objectCount; i++)
    {
        if (!world->objects[i].active)
            continue;

        if (xCheckCollisionAABB(collider, world->objects[i].collider))
        {
            return true;
        }
    }

    return false;
}

static void xUpdatePlayerAnimation(Player *player)
{
    // ---------------- SELECT SPRITE ROW ----------------

    int totalFrames = xGetAnimationLength(player->state);


    // ---------------- ANIMATION TIMER ----------------

    // Advance to the next animation frame.
    player->animationTimer += GetFrameTime();

    while (player->animationTimer >= player->interval)
    {
        player->currentFrame++;

        if (player->state == PLAYER_ATTACK)
        {
            // Play attack animation once.
            if (player->currentFrame >= totalFrames)
            {
                player->currentFrame = 0;

                // Return to the correct state.
                if ((player->moveX != 0 || player->moveY != 0))
                {
                    player->state = PLAYER_WALK;
                }
                else
                {
                    player->state = PLAYER_IDLE;
                }
            }
        }
        else 
        {   
            // Loop idle/walk animation.
            if (player->currentFrame >= totalFrames)
            {
                player->currentFrame = 0;
            }
        }

        player->animationTimer -= player->interval;
    }

    player->gameObject.source.y =
        xGetAnimationRow(player->state, player->direction)
        * player->frameHeight;

    player->gameObject.source.x = player->currentFrame * player->frameWidth;
    
    player->gameObject.source.width = player->frameWidth;
    player->gameObject.source.height = player->frameHeight;
}

bool xSavePlayer(const Player *player)
{
    FILE *file = fopen(PATH_SAVEFILE, "wb");
    
    // If open failed, return false.
    if (file == NULL)
    {
        perror("Failed to open save file");
        return false;
    }
    
    // Temporary struct to pass on values to save.
    PlayerSave save =
    {
        .dest = player->gameObject.dest,
        .speed = player->speed,
        .state = player->state,
        .direction = player->direction,
        .flip = player->gameObject.flip
    };

    // Keeping track of write's success.
    bool success = (fwrite(&save, sizeof(save), 1, file) == 1);
    
    fclose(file);

    return success;
}

bool xLoadPlayer(Player *player)
{
    FILE *file = fopen(PATH_SAVEFILE, "rb");

    // If open failed, return false.
    if (file == NULL)
    {
        perror("Failed to open save file");
        return false;
    }

    PlayerSave save;

    bool success = (fread(&save, sizeof(save), 1, file) == 1);

    fclose(file);

    // If read is unsuccessful, return false.
    if (!success)
        return false;

    player->gameObject.dest = save.dest;
    player->speed = save.speed;
    player->state = save.state;
    player->direction = save.direction;
    player->gameObject.flip = save.flip;

    // After data has been read from file, return true.
    return true;
}

static int xGetAnimationLength(PlayerState state)
{
    switch (state)
    {
        case PLAYER_ATTACK:
            return 4;
        
        case PLAYER_IDLE:
        case PLAYER_WALK:
            return 6;

        default:
            return 0;
    }
}

static int xGetAnimationRow(PlayerState state, PlayerDirection direction)
{
    switch (state)
    {
        case PLAYER_IDLE:

            switch (direction)
            {
                case PLAYER_FACE_FRONT:
                    return 0;
                
                case PLAYER_FACE_LEFT:
                case PLAYER_FACE_RIGHT:
                    return 1;

                case PLAYER_FACE_BACK:
                    return 2;

                default:
                    return 0;

            }

        case PLAYER_WALK:
            
            switch (direction)
            {
                case PLAYER_FACE_FRONT:
                    return 3;

                case PLAYER_FACE_LEFT:
                case PLAYER_FACE_RIGHT:
                    return 4;

                case PLAYER_FACE_BACK:
                    return 5;
                
                default:
                    return 3;

            }

        case PLAYER_ATTACK:
            
            switch (direction)
            {
                case PLAYER_FACE_FRONT:
                    return 6;

                case PLAYER_FACE_LEFT:
                case PLAYER_FACE_RIGHT:
                    return 7;

                case PLAYER_FACE_BACK:
                    return 8;

                default:
                    return 6;
            }
    }

    return 0;
}