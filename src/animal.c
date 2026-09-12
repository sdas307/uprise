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
static void xAnimalWandering(Animal *animal, World *world, float dt);

/// Update animal sprites to show animation.
static void xAnimateAnimal(Animal *animal, float dt);

/// Set target values (x and y) for the animal.
static void xAnimalSetTarget(Animal *animal);

/// Whether to stay idle based on percentages. 
static bool xStayIdle();

/// Check animal collision with world entities.
static bool xAnimalCheckCollision(World *world, xRectangle collider);

/// Get the number of frames for animation.
static int xGetAnimationLength(AnimalState state);

/// Get the row index of the animation in question.
static int xGetAnimationRow(AnimalState state);

static const int idleChance = 30;

const xRectangle wanderZone = 
{
    1000,
    1200,
    64 * 7,
    64 * 5
};

/* ---------- Implementation ----------*/

static void xInitAnimal(Animal *animal)
{
    animal->entity.type = ANIMAL;

    animal->moveX = 0;
    animal->moveY = 0;

    animal->targetX = 0.0f;
    animal->targetY = 0.0f;
    animal->isTargetSet = false;
    animal->isIdleSet = false;
    animal->idleDuration = 0;
    animal->dt = 0.0f;

    animal->animIdleInterval = 0.6f;
    animal->animMovingInterval = 0.20f;
    animal->animTimer = 0.0f;

    animal->currentFrame = 0;

    animal->state = ANIMAL_IDLE;
    animal->direction = ANIMAL_LEFT;

    // animal->randomInterval = 0.0f;
    // animal->randomStateTimer = 0;

    animal->entity.gameObject.active = true;
    animal->entity.gameObject.collidable = true;
}

void xUpdateAnimal(Animal *animal, World *world, float dt)
{
    xAnimateAnimal(animal, dt);
    xAnimalWandering(animal, world, dt);
}

static void xAnimalWandering(Animal *animal, World *world, float dt)
{
    // No current activity: decide whether to move or stay idle.
    if (!animal->isTargetSet && !animal->isIdleSet)
    {
        if (xStayIdle() == false)
        {
            xAnimalSetTarget(animal);
            animal->isTargetSet = true;
            animal->state = ANIMAL_MOVING;
        }
        else
        {
            animal->idleDuration = GetRandomValue(1, 3);
            animal->isIdleSet = true;
            animal->state = ANIMAL_IDLE;
        }
    }
    
    // Currently idling.
    if (animal->isIdleSet)
    {
        animal->dt += dt;

        if (animal->dt > animal->idleDuration)
        {
            animal->isIdleSet = false;
            animal->dt = 0.0f;
        }

        return;
    }

    // Currently moving toward target.
    if (animal->isTargetSet)
    {
        xVector2 movement =
        {
            animal->targetX - animal->entity.gameObject.dest.x,
            animal->targetY - animal->entity.gameObject.dest.y
        };
        
        float distance = Vector2Length(movement);
        float step = animal->speed * dt;

        // Reached target point.
        if (distance <= step)
        {
            animal->entity.gameObject.dest.x = animal->targetX;
            animal->entity.gameObject.dest.y = animal->targetY;

            animal->isTargetSet = false;

            return;
        }

        movement = Vector2Normalize(movement);

        movement.x *= animal->speed * dt;
        movement.y *= animal->speed * dt;

        // If moving right -> flip.
        animal->entity.gameObject.flip = (movement.x > 0);

        // X-axis
        xRectangle nextCollider = animal->entity.gameObject.collider;
        nextCollider.x += movement.x;

        if (!xAnimalCheckCollision(world, nextCollider))
        {
            animal->entity.gameObject.dest.x += movement.x;
            animal->entity.gameObject.collider.x = nextCollider.x;
        }

        // Y-axis
        nextCollider = animal->entity.gameObject.collider;
        nextCollider.y += movement.y;

        if (!xAnimalCheckCollision(world, nextCollider))
        {
            animal->entity.gameObject.dest.y += movement.y;
            animal->entity.gameObject.collider.y = nextCollider.y;
        }

        animal->entity.gameObject.depth = animal->entity.gameObject.collider.y + animal->entity.gameObject.collider.height;
    }
}

static void xAnimalSetTarget(Animal *animal)
{
    animal->targetX = GetRandomValue((int)wanderZone.x, (int)(wanderZone.x + wanderZone.width));
    animal->targetY = GetRandomValue((int)wanderZone.y, (int)(wanderZone.y + wanderZone.height));
}

static bool xStayIdle()
{
    int random = GetRandomValue(1, 100);

    if (random >= idleChance)
        return true;
    else
        return false;
}

static void xAnimateAnimal(Animal *animal, float dt)
{
    int totalFrames = xGetAnimationLength(animal->state);

    animal->animTimer += dt;

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

    animal->entity.gameObject.source.x = animal->currentFrame * animal->frameWidth;

    animal->entity.gameObject.source.y = xGetAnimationRow(animal->state) * animal->frameHeight;

    animal->entity.gameObject.source.width = animal->frameWidth;
    animal->entity.gameObject.source.height = animal->frameHeight;
}

static bool xAnimalCheckCollision(World *world, xRectangle collider)
{
    for (int i = 0; i < world->entityCount; i++)
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
    UnloadTexture(animal->entity.gameObject.texture);
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

    animal->entity.gameObject.texture = LoadTexture(PATH_CHICKEN_SHEET);
    SetTextureFilter(animal->entity.gameObject.texture, TEXTURE_FILTER_POINT);

    animal->entity.gameObject.source = SRC_CHICKEN;
    animal->entity.gameObject.dest = dest;

    animal->entity.gameObject.collider = (xRectangle)
    {
        animal->entity.gameObject.dest.x + 12,
        animal->entity.gameObject.dest.y + 36,
        animal->entity.gameObject.dest.width - 24,
        16
    };

    animal->entity.gameObject.depth = animal->entity.gameObject.collider.y + animal->entity.gameObject.collider.height;

    animal->speed = 64;
    animal->entity.gameObject.flip = false;
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

    animal->entity.gameObject.texture = LoadTexture(PATH_SHEEP_SHEET);
    SetTextureFilter(animal->entity.gameObject.texture, TEXTURE_FILTER_POINT);

    animal->entity.gameObject.source = SRC_SHEEP;
    animal->entity.gameObject.dest = dest;

    animal->entity.gameObject.collider = (xRectangle){
        animal->entity.gameObject.dest.x + 36,
        animal->entity.gameObject.dest.y + 68,
        animal->entity.gameObject.dest.width - 72,
        20
    };

    animal->entity.gameObject.depth = animal->entity.gameObject.collider.y + animal->entity.gameObject.collider.height;

    animal->speed = 128;
    animal->entity.gameObject.flip = false;
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

    animal->entity.gameObject.texture = LoadTexture(PATH_PIG_SHEET);
    SetTextureFilter(animal->entity.gameObject.texture, TEXTURE_FILTER_POINT);

    animal->entity.gameObject.source = SRC_PIG;
    animal->entity.gameObject.dest = dest;

    animal->entity.gameObject.collider = (xRectangle){
        animal->entity.gameObject.dest.x + 36,
        animal->entity.gameObject.dest.y + 68,
        animal->entity.gameObject.dest.width - 72,
        20
    };

    animal->entity.gameObject.depth = animal->entity.gameObject.collider.y + animal->entity.gameObject.collider.height;

    animal->speed = 64;
    animal->entity.gameObject.flip = false;
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

    animal->entity.gameObject.texture = LoadTexture(PATH_COW_SHEET);

    animal->entity.gameObject.source = SRC_COW;

    animal->entity.gameObject.dest = dest;

    animal->entity.gameObject.collider = (xRectangle){
        animal->entity.gameObject.dest.x + 28,
        animal->entity.gameObject.dest.y + 72,
        animal->entity.gameObject.dest.width - 56,
        24
    };

    animal->entity.gameObject.depth = animal->entity.gameObject.collider.y + animal->entity.gameObject.collider.height;

    animal->speed = 64;
    animal->entity.gameObject.flip = false;
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