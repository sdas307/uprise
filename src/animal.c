#include "animal.h"
#include "config.h"
#include "assets.h"
#include "sprites.h"
#include "raymath.h"
#include "world.h"

#include <stdio.h>

/* ---------- Signatures ----------*/

/// Initialize animal with default values
static void xInitAnimal(Animal *animal);

/// Move animal based on wandering AI logic.
static void xMoveAnimal(Animal *animal, World *world);

/// Update animal sprites to show animation.
static void xAnimateAnimal(Animal *animal);

/// Reset all AI movement related values.
static void xResetMoveValues(Animal *animal);

/// Set moveX value based on state and direction.
static void xSetAnimalMoveX(Animal *animal);

/// Check animal collision with world entities.
static bool xAnimalCheckCollision(World *world, xRectangle collider);

/// Get the number of frames for animation.
static int xGetAnimationLength(AnimalState state);

/// Get the row index of the animation in question.
static int xGetAnimationRow(AnimalState state);

/* ---------- Implementation ----------*/

static void xInitAnimal(Animal *animal)
{
    animal->gameObject.type = OBJECT_ANIMAL;

    animal->moveX = 0;
    animal->moveY = 0;

    animal->animIdleInterval = 0.6f;
    animal->animMovingInterval = 0.20f;
    animal->animTimer = 0.0f;

    animal->currentFrame = 0;

    animal->state = ANIMAL_IDLE;
    animal->direction = ANIMAL_LEFT;

    animal->randomInterval = 0.0f;
    animal->randomStateTimer = 0;

    animal->gameObject.active = true;
    animal->gameObject.collidable = true;
}

void xUpdateAnimal(Animal *animal, World *world)
{
    xAnimateAnimal(animal);
    xMoveAnimal(animal, world);
}

static void xMoveAnimal(Animal *animal, World *world)
{
    if (animal->randomInterval > animal->randomStateTimer)
    {
        xResetMoveValues(animal);
    }

    animal->randomInterval += GetFrameTime();

    xSetAnimalMoveX(animal);

    xVector2 movement = {animal->moveX, animal->moveY};
    // printf("\n\n moveX: %d\n\n", animal->moveX);

    if (Vector2Length(movement) == 0)
        return;

    // Normalize diagonal movement to maintain a constant speed.
    // movement = Vector2Normalize(movement);

    xRectangle nextCollider = animal->gameObject.collider;
    nextCollider.x += movement.x * animal->speed;

    if (!xAnimalCheckCollision(world, nextCollider))
    {
        animal->gameObject.dest.x += movement.x * animal->speed;

        animal->gameObject.collider = nextCollider;
    }
}

static void xResetMoveValues(Animal *animal)
{
    animal->randomInterval = 0;
    animal->randomStateTimer = GetRandomValue(0, animal->stateTimerMax);

    animal->moveX = 0;
    animal->moveY = 0;

    animal->state = GetRandomValue(ANIMAL_IDLE, ANIMAL_MOVING);
    animal->direction = GetRandomValue(ANIMAL_LEFT, ANIMAL_RIGHT);
}

static void xSetAnimalMoveX(Animal *animal)
{
    switch (animal->state)
    {
    case ANIMAL_IDLE:
        animal->moveX = 0;
    break;

    case ANIMAL_MOVING:

        switch (animal->direction)
        {
        case ANIMAL_LEFT:
            animal->gameObject.flip = false;
            animal->moveX = -1;
        break;

        case ANIMAL_RIGHT:
            animal->gameObject.flip = true;
            animal->moveX = 1;
        break;

        default:
            animal->moveX = 0;
        break;
        }

        break;
    }
}

static void xAnimateAnimal(Animal *animal)
{
    int totalFrames = xGetAnimationLength(animal->state);

    animal->animTimer += GetFrameTime();

    switch (animal->state)
    {

    case ANIMAL_IDLE:

        while (animal->animTimer >= animal->animIdleInterval)
        {
            animal->currentFrame++;
            animal->animTimer -= animal->animIdleInterval;
        }

        if (animal->currentFrame >= totalFrames)
        {
            animal->currentFrame = 0;
        }

    break;
    case ANIMAL_MOVING:

        while (animal->animTimer >= animal->animMovingInterval)
        {
            animal->currentFrame++;
            animal->animTimer -= animal->animMovingInterval;
        }

        if (animal->currentFrame >= totalFrames)
        {
            animal->currentFrame = 0;
        }

    break;
    }

    animal->gameObject.source.x = animal->currentFrame * animal->frameWidth;

    animal->gameObject.source.y = xGetAnimationRow(animal->state) * animal->frameHeight;

    animal->gameObject.source.width = animal->frameWidth;
    animal->gameObject.source.height = animal->frameHeight;
}

static bool xAnimalCheckCollision(World *world, xRectangle collider)
{
    for (int i = 0; i <= world->entityCount; i++)
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

void xUnloadAnimal(Animal *animal)
{
    UnloadTexture(animal->gameObject.texture);
}

void xSpawnChicken(AnimalManager *manager, xRectangle dest)
{
    // If max number of animals are present, return.
    if (manager->animalCount >= MAX_ANIMALS)
        return;

    Animal *animal = &manager->animals[manager->animalCount++];

    xInitAnimal(animal);
    animal->frameWidth = 64;
    animal->frameHeight = 64;

    animal->type = ANIMAL_CHICKEN;

    animal->gameObject.texture = LoadTexture(PATH_CHICKEN_SHEET);
    SetTextureFilter(animal->gameObject.texture, TEXTURE_FILTER_POINT);

    animal->gameObject.source = RECT_CHICKEN;
    animal->gameObject.dest = dest;

    animal->gameObject.collider = (xRectangle){
        animal->gameObject.dest.x + 12,
        animal->gameObject.dest.y + 36,
        animal->gameObject.dest.width - 24,
        16};

    animal->gameObject.depth = animal->gameObject.collider.y + animal->gameObject.collider.height;

    animal->stateTimerMax = 1;

    animal->speed = 2;
    animal->gameObject.flip = false;
}

void xSpawnSheep(AnimalManager *manager, xRectangle dest)
{
    // If max number of animals are present, return.
    if (manager->animalCount >= MAX_ANIMALS)
        return;

    Animal *animal = &manager->animals[manager->animalCount++];

    xInitAnimal(animal);
    animal->frameWidth = 128;
    animal->frameHeight = 128;

    animal->type = ANIMAL_SHEEP;

    animal->gameObject.texture = LoadTexture(PATH_SHEEP_SHEET);
    SetTextureFilter(animal->gameObject.texture, TEXTURE_FILTER_POINT);

    animal->gameObject.source = RECT_SHEEP;
    animal->gameObject.dest = dest;

    animal->gameObject.collider = (xRectangle){
        animal->gameObject.dest.x + 16,
        animal->gameObject.dest.y + 50,
        animal->gameObject.dest.width - 32,
        30};

    animal->gameObject.depth = animal->gameObject.collider.y + animal->gameObject.collider.height;

    animal->speed = 2;
    animal->gameObject.flip = false;
}

void xSpawnPig(AnimalManager *manager, xRectangle dest)
{
    // If max number of animals are present, return.
    if (manager->animalCount >= MAX_ANIMALS)
        return;

    Animal *animal = &manager->animals[manager->animalCount++];

    xInitAnimal(animal);
    animal->frameWidth = 128;
    animal->frameHeight = 128;

    animal->type = ANIMAL_PIG;

    animal->gameObject.texture = LoadTexture(PATH_PIG_SHEET);
    SetTextureFilter(animal->gameObject.texture, TEXTURE_FILTER_POINT);

    animal->gameObject.source = RECT_PIG;
    animal->gameObject.dest = dest;

    animal->gameObject.collider = (xRectangle){
        animal->gameObject.dest.x + 16,
        animal->gameObject.dest.y + 50,
        animal->gameObject.dest.width - 32,
        30};

    animal->gameObject.depth = animal->gameObject.collider.y + animal->gameObject.collider.height;

    animal->speed = 2;
    animal->gameObject.flip = false;
}

void xSpawnCow(AnimalManager *manager, xRectangle dest)
{
    // If max number of animals are present, return.
    if (manager->animalCount >= MAX_ANIMALS)
        return;

    // Create new animal
    Animal *animal = &manager->animals[manager->animalCount++];

    xInitAnimal(animal);
    animal->frameWidth = 128;
    animal->frameHeight = 128;

    animal->type = ANIMAL_COW;

    animal->gameObject.texture = LoadTexture(PATH_COW_SHEET);

    animal->gameObject.source = RECT_COW;

    animal->gameObject.dest = dest;

    animal->gameObject.collider = (xRectangle){
        animal->gameObject.dest.x + 36,
        animal->gameObject.dest.y + 66,
        animal->gameObject.dest.width - 64,
        30};

    animal->gameObject.depth = animal->gameObject.collider.y + animal->gameObject.collider.height;

    animal->stateTimerMax = 3;

    animal->speed = 2;
    animal->gameObject.flip = false;
}

static int xGetAnimationLength(AnimalState state)
{
    switch (state)
    {
    case ANIMAL_IDLE:
        return 2;

    case ANIMAL_MOVING:
        return 2;

    default:
        return 2;
    }
}

static int xGetAnimationRow(AnimalState state)
{
    switch (state)
    {
    case ANIMAL_IDLE:
        return 0;

    case ANIMAL_MOVING:
        return 1;

    default:
        return 0;
    }
}