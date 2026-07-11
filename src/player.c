#include "player.h"
#include "config.h"

#include "raymath.h"
#include <stdio.h>

/* ---------- Signatures ---------- */

/// Check collisions between player and world objects
static bool xCheckCollision(World *world, Rectangle collider);

/// Move player based on user input.
static void xMovePlayer(Player *player, World *world);

/// Update player sprites to show animation.
static void xUpdatePlayerAnimation(Player *player);


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

static float deltaTime = 0.0f;
// static const float interval = 0.10f;

static const int totalFrames = 6;
static const int frameWidth = 32;
static const int frameHeight = 32;

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

    player->gameObject.source = (xRectangle) {0, 0, frameWidth, frameHeight};
    player->gameObject.dest = (xRectangle) {config.x, config.y, frameWidth * 4, frameHeight * 4};

    player->gameObject.active = true;

    player->gameObject.collider = (xRectangle)
    {
        player->gameObject.dest.x + 42,
        player->gameObject.dest.y + 80,
        40,
        12,
    };

    player->gameObject.depth = player->gameObject.collider.y + player->gameObject.collider.height;

    player->speed = config.speed;
    printf("speed = %d", config.speed);
    
    player->state = PLAYER_IDLE;
    player->direction = PLAYER_FACE_FRONT;
    player->gameObject.flip = false;
}

void xUpdatePlayer(Player *player, World *world)
{
    xMovePlayer(player, world);
    xUpdatePlayerAnimation(player);
    DrawRectangleLinesEx(player->gameObject.dest, 1.0f, RED);
}

void xUnloadPlayer(Player *player)
{
    UnloadTexture(player->gameObject.texture);
}

static void xMovePlayer(Player *player, World *world)
{
    int dx = 0;     // movement vector's x
    int dy = 0;     // movement vector's y

    bool moving = false;

    if (IsKeyDown(KEY_W) && player->gameObject.dest.y >= 0)
    {
        player->state = PLAYER_WALKING;
        player->direction = PLAYER_FACE_BACK;

        dy--;
        moving = true;
    }

    if (IsKeyDown(KEY_S) && player->gameObject.dest.y <= SCREEN_HEIGHT - frameHeight * 4)
    {
        player->state = PLAYER_WALKING;
        player->direction = PLAYER_FACE_FRONT;

        dy++;
        moving = true;
    }

    if (IsKeyDown(KEY_A) && player->gameObject.dest.x >= 0)
    {
        player->state = PLAYER_WALKING;
        player->direction = PLAYER_FACE_LEFT;

        player->gameObject.flip = true;
        
        dx--;
        moving = true;
    }

    if (IsKeyDown(KEY_D) && player->gameObject.dest.x <= SCREEN_WIDTH - frameWidth * 4)
    {
        player->state = PLAYER_WALKING;
        player->direction = PLAYER_FACE_RIGHT;

        player->gameObject.flip = false;
        
        dx++;
        moving = true;
    }

    if (!moving)
    {
        player->state = PLAYER_IDLE;

        dx = 0;     // reset dx
        dy = 0;     // reset dy
    }
    
    // Create a movement vector from player input.
    // Essentially copy values every frame (only 2 (int) floats: x, y)
    xVector2 movement = {dx, dy};
    xRectangle nextCollider;

    if (Vector2Length(movement) == 0)
        return;

    // Normalize diagonal movement to maintain a constant speed.
    movement = Vector2Normalize(movement);

    nextCollider = player->gameObject.collider;
    nextCollider.x += movement.x * player->speed;
    nextCollider.y += movement.y * player->speed;

    if (!xCheckCollision(world, nextCollider))
    {
        player->gameObject.dest.x += movement.x * player->speed;
        player->gameObject.dest.y += movement.y * player->speed;

        player->gameObject.collider = nextCollider;
    }
}

bool xCheckCollision(World *world, Rectangle collider)
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

    if (player->state == PLAYER_IDLE)
    {
        // Select the correct animation row.
        switch (player->direction)
        {
        case PLAYER_FACE_FRONT:
            player->gameObject.source.y = frameHeight * 0;
            break;

        case PLAYER_FACE_LEFT:
        case PLAYER_FACE_RIGHT:
            player->gameObject.source.y = frameHeight * 1;
            break;

        case PLAYER_FACE_BACK:
            player->gameObject.source.y = frameHeight * 2;
            break;
        }
    }

    else if (player->state == PLAYER_WALKING)
    {
        // Select the correct animation row.
        switch (player->direction)
        {
        case PLAYER_FACE_FRONT:
            player->gameObject.source.y = frameHeight * 3;
            break;

        case PLAYER_FACE_LEFT:
        case PLAYER_FACE_RIGHT:
            player->gameObject.source.y = frameHeight * 4;
            break;

        case PLAYER_FACE_BACK:
            player->gameObject.source.y = frameHeight * 5;
            break;
        }
    }

    // ---------------- ANIMATION TIMER ----------------

    // Advance to the next animation frame.
    deltaTime += GetFrameTime();

    if (deltaTime >= player->interval)
    {
        player->gameObject.source.x += frameWidth;

        if (player->gameObject.source.x >= frameWidth * totalFrames)
        {
            player->gameObject.source.x = 0;
        }

        deltaTime -= player->interval;
    }

    player->gameObject.source.width = frameWidth;
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