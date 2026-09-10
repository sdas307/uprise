#include "player.h"
#include "config.h"
#include "assets.h"

#include "raymath.h"
#include <stdio.h>

/* ---------- Signatures ---------- */

/// Check collisions between player and world objects
static bool xCheckCollision(World *world, xRectangle collider);

// static bool xOutsideScreen(Player *player, xRectangle collider);

/// Handle user input (keyboard/mouse).
static void xReadPlayerInput(Player *player);

/// Update player state based on user input.
static void xUpdatePlayerState(Player *player);

/// Move player based on user input.
static void xMovePlayer(Player *player, World *world, float dt);

/// Update player sprites to show animation.
static void xUpdatePlayerAnimation(Player *player, float dt);

/// Get the number of frames for animation.
static int xGetAnimationLength(PlayerState state, PlayerEquipment equipment);

/// Get the row index of the animation in question (with and without epuipment in hand).
static int xGetAnimationRow(PlayerState state, PlayerEquipment equipment, PlayerDirection direction);

/// Get the idle animations row index from spritesheet. 
static int getAnimationIdleRow(PlayerEquipment equipment, PlayerDirection direction);

/// Get the walking animations row index from spritesheet (with and without epuipment in hand).
static int getAnimationWalkRow(PlayerEquipment equipment, PlayerDirection direction);

/// Get the attack animations row index from spritesheet (with and without epuipment in hand).
static int getAnimationAttackRow(PlayerState state, PlayerEquipment equipment, PlayerDirection direction);


/* ---------- Implementation ---------- */

typedef struct PlayerConfig
{
    int x;              // Player spawn x.
    int y;              // Player spawn y.
    int walk_speed;     // Player walking speed.
    int run_speed;      // Player running speed.

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
        fscanf(file, " walk_speed = %d", &config->walk_speed) != 1 ||
        fscanf(file, " run_speed = %d", &config->run_speed) != 1)
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
        .walk_speed = 160,
        .run_speed = 256
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
    player->walkInterval = 0.10f;
    player->runInterval = 0.09f;
    player->waterInterval = 0.15f;

    player->animationTimer = 0.0f;
    player->currentFrame = 0;

    player->frameWidth = 256;
    player->frameHeight = 256;

    player->equipment = EQUIP_HOE;

    player->gameObject.source = (xRectangle) {0, 0, player->frameWidth, player->frameHeight};
    player->gameObject.dest = (xRectangle) {config.x, config.y, player->frameWidth, player->frameHeight};

    player->gameObject.type = OBJECT_PLAYER;

    player->gameObject.active = true;

    player->attackPressed = false;
    player->isRunning = false;

    player->gameObject.collider = (xRectangle)
    {
        player->gameObject.dest.x + 108,
        player->gameObject.dest.y + 144,
        36,
        12,
    };

    player->gameObject.depth = player->gameObject.collider.y + player->gameObject.collider.height;

    player->speed = config.walk_speed;
    // printf("speed = %d", config.speed);
    player->walkSpeed = config.walk_speed;
    player->runSpeed = config.run_speed;
    
    player->state = PLAYER_IDLE;
    player->direction = PLAYER_FACE_FRONT;
    player->gameObject.flip = false;
}

void xUpdatePlayer(Player *player, World *world, xCamera2D camera, float dt)
{
    xReadPlayerInput(player);
    xUpdatePlayerState(player);
    xMovePlayer(player, world, dt);
    xUpdatePlayerAnimation(player, dt);
    xUpdateInteraction(&player->target, world, camera, (xVector2){player->gameObject.collider.x, player->gameObject.collider.y});
    // DrawRectangleLinesEx(player->gameObject.dest, 1.0f, RED);
}

void xUnloadPlayer(Player *player)
{
    UnloadTexture(player->gameObject.texture);
}

static void xReadPlayerInput(Player *player)
{
    player->moveX = 0;
    player->moveY = 0;

    // Shift held down -> Faster movement speed.
    if (IsKeyDown(KEY_LEFT_SHIFT))
    {
        player->isRunning = true;
        player->speed = player->runSpeed;
    }

    // Shift released -> Usual movement speed.
    if (IsKeyReleased(KEY_LEFT_SHIFT))
    {
        player->isRunning = false;
        player->speed = player->walkSpeed;
    }

    if (IsKeyPressed(KEY_F11))
        ToggleFullscreen();

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

static void xMovePlayer(Player *player, World *world, float dt)
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

    movement.x *= player->speed * dt;
    movement.y *= player->speed * dt;

    // X-axis
    xRectangle nextCollider = player->gameObject.collider;
    nextCollider.x += movement.x;

    if (!xCheckCollision(world, nextCollider))
    {
        player->gameObject.dest.x += movement.x;
        player->gameObject.collider.x = nextCollider.x;
    }
    
    // Y-axis
    nextCollider = player->gameObject.collider;
    nextCollider.y += movement.y;

    if (!xCheckCollision(world, nextCollider))
    {
        player->gameObject.dest.y += movement.y;
        player->gameObject.collider.y = nextCollider.y;
    }

    player->gameObject.depth = player->gameObject.collider.y + player->gameObject.collider.height;
}

static bool xCheckCollision(World *world, xRectangle collider)
{
    for (int i=0; i < world->entityCount; i++)
    {
        if (!world->entities[i].gameObject.active)
            continue;

        if (!world->entities[i].gameObject.collidable)
            continue;
        
        if (xCheckCollisionAABB(collider, world->entities[i].gameObject.collider))
        {
            return true;
        }
    }

    return false;
}

static void xUpdatePlayerAnimation(Player *player, float dt)
{
    // ---------------- SELECT SPRITE ROW ----------------

    int totalFrames = xGetAnimationLength(player->state, player->equipment);


    // ---------------- ANIMATION TIMER ----------------

    // Advance to the next animation frame.
    player->animationTimer += dt;

    // If player is running, set the interval to a faster rate.
    // player->interval = player->isRunning ? player->runInterval : player->walkInterval;

    if (player->isRunning)
    {
        player->interval = player->runInterval;
    }
    else
    {
        player->interval = player->walkInterval;
    }

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
        xGetAnimationRow(player->state, player->equipment, player->direction)
        * WORLD_GRID_SIZE;

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

static int xGetAnimationLength(PlayerState state, PlayerEquipment equipment)
{
    switch (state)
    {
        case PLAYER_ATTACK:
            switch (equipment)
            {
                case EQUIP_NONE:
                case EQUIP_SWORD:
                    return 4;
                    
                default:
                    return 6;
            }
        break;
        
        case PLAYER_IDLE:
        case PLAYER_WALK:
            return 6;

        case PLAYER_FISHING:
            return 9;

        default:
            // Safe fallback animation length - 0.
            return 0;
    }
}

static int xGetAnimationRow(PlayerState state, PlayerEquipment equipment, PlayerDirection direction)
{
    switch (state)
    {
        case PLAYER_IDLE:
            return getAnimationIdleRow(equipment, direction);

        case PLAYER_WALK:
            return getAnimationWalkRow(equipment, direction);

        case PLAYER_ATTACK:
            return getAnimationAttackRow(state, equipment, direction);

        case PLAYER_FISHING:
            return -1; // #############################
    }

    // Failed to get appropriate sprite row.
    return -1;
}

static int getAnimationIdleRow(PlayerEquipment equipment, PlayerDirection direction)
{
    switch (equipment)
    {
        case EQUIP_NONE:
        case EQUIP_PICKAXE:
        case EQUIP_AXE:
        case EQUIP_HOE:
            switch (direction)
            {
            case PLAYER_FACE_FRONT:
                return 0;

            case PLAYER_FACE_LEFT:
            case PLAYER_FACE_RIGHT:
                return 4;

            case PLAYER_FACE_BACK:
                return 8;
            }
        break;

        case EQUIP_LANTERN:
            switch (direction)
            {
            case PLAYER_FACE_FRONT:
                return 0;
            
            case PLAYER_FACE_LEFT:
            case PLAYER_FACE_RIGHT:
                return 4;

            case PLAYER_FACE_BACK:
                return 8;
            }
        break;

        case EQUIP_TORCH:
            switch (direction)
            {
            case PLAYER_FACE_FRONT:
                    return 24;
                
            case PLAYER_FACE_LEFT:
            case PLAYER_FACE_RIGHT:
                return 28;

            case PLAYER_FACE_BACK:
                return 32;
            }
        break;
    }

    // Couldn't find appropriate sprite index.
    return -1;
}

static int getAnimationWalkRow(PlayerEquipment equipment, PlayerDirection direction)
{
    switch (equipment)
    {
        case EQUIP_NONE:
        case EQUIP_AXE:
        case EQUIP_PICKAXE:
        case EQUIP_HOE:
            switch (direction)
            {
                case PLAYER_FACE_FRONT:
                    return 12;

                case PLAYER_FACE_LEFT:
                case PLAYER_FACE_RIGHT:
                    return 16;

                case PLAYER_FACE_BACK:
                    return 20;
            }
        break;

        case EQUIP_LANTERN:
            switch (direction)
            {
                case PLAYER_FACE_FRONT:
                        return 12;
                    
                case PLAYER_FACE_LEFT:
                case PLAYER_FACE_RIGHT:
                    return 16;

                case PLAYER_FACE_BACK:
                    return 20;
            }
        break;

        case EQUIP_TORCH:
            switch (direction)
            {
                case PLAYER_FACE_FRONT:
                    return 36;
                    
                case PLAYER_FACE_LEFT:
                case PLAYER_FACE_RIGHT:
                    return 40;

                case PLAYER_FACE_BACK:
                    return 44;
            }
        break;
    }
    
    // Could not find appropriate sprite index.
    return -1;
}

static int getAnimationAttackRow(PlayerState state, PlayerEquipment equipment, PlayerDirection direction)
{
    switch (equipment)
    {
        case EQUIP_NONE:
        case EQUIP_SWORD:
            switch (direction)
            {
                case PLAYER_FACE_FRONT:
                    return 24;

                case PLAYER_FACE_LEFT:
                case PLAYER_FACE_RIGHT:
                    return 36;

                case PLAYER_FACE_BACK:
                    return 48;
            }
        break;

        case EQUIP_BO:
            switch (direction)
            {
                case PLAYER_FACE_FRONT:
                    return 116;

                case PLAYER_FACE_LEFT:
                case PLAYER_FACE_RIGHT:
                    return 120;

                case PLAYER_FACE_BACK:
                    return 124;
            }
        break;

        case EQUIP_AXE:
            switch (state)
            {
                case PLAYER_ATTACK:
                    switch (direction)
                    {
                    case PLAYER_FACE_FRONT:
                        return 128;

                    case PLAYER_FACE_LEFT:
                    case PLAYER_FACE_RIGHT:
                        return 132;

                    case PLAYER_FACE_BACK:
                        return 136;
                    }
                break;
        }
            
        break;

        case EQUIP_PICKAXE:
            switch (direction)
            {
                case PLAYER_FACE_FRONT:
                    return 140;

                case PLAYER_FACE_LEFT:
                case PLAYER_FACE_RIGHT:
                    return 144;

                case PLAYER_FACE_BACK:
                    return 148;
            }
        break;

        case EQUIP_HOE:
            switch (direction)
            {
                case PLAYER_FACE_FRONT:
                    return 152;

                case PLAYER_FACE_LEFT:
                case PLAYER_FACE_RIGHT:
                    return 156;

                case PLAYER_FACE_BACK:
                    return 160;
            }
        break;
        
        case EQUIP_WATERING_CAN:
            switch (direction)
            {
                case PLAYER_FACE_FRONT:
                    return 164;

                case PLAYER_FACE_LEFT:
                case PLAYER_FACE_RIGHT:
                    return 168;

                case PLAYER_FACE_BACK:
                    return 172;
            }
        break;
    }

    // Failed to find appropriate sprite index.
    return -1;
}