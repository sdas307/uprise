#include "animal.h"
#include "config.h"
#include "assets.h"

#include <stdio.h>

/* ---------- Signatures ----------*/

static void xMoveAnimal(Animal *animal);

static void xInitAnimal(Animal *animal);

static void xAnimateAnimal(Animal *animal);

static int xGetAnimationLength(AnimalState state);

static int xGetAnimationRow(AnimalState state);

static float randomInterval = 0.0f;
static float r = 0.0f;
static int randomValue = 0;


/* ---------- Implementation ----------*/

static void xInitAnimal(Animal *animal)
{
    animal->animationInterval = 0.6f;
    animal->animationTimer = 0.0f;

    animal->currentFrame = 0;

    animal->state = ANIMAL_IDLE;
    animal->direction = ANIMAL_LEFT;

    animal->gameObject.type = OBJECT_ANIMAL;

    animal->gameObject.active = true;
}

void xUpdateAnimal(Animal *animal)
{
    xAnimateAnimal(animal);
    xMoveAnimal(animal);
}

static void xMoveAnimal(Animal *animal)
{
    // if (randomValue == 0)
    //     randomValue = GetRandomValue(0, 3);

    // if (randomValue > 3)
    //     randomValue = GetRandomValue(0, 3);

    // r += GetFrameTime();

    // if (r >= randomValue)
    // {
    //     animal->state = GetRandomValue(ANIMAL_IDLE, ANIMAL_MOVING);
    //     r = 0;
    // }

    // if (animal->state == ANIMAL_MOVING)
    // {
    //     animal->direction = GetRandomValue(ANIMAL_LEFT, ANIMAL_RIGHT);
    // }
    
    // if (animal->direction == ANIMAL_LEFT)
    // {
    //     animal->gameObject.flip = false;
    //     animal->gameObject.dest.x -= animal->speed;
    // }

    // if (animal->direction == ANIMAL_RIGHT)
    // {
    //     animal->gameObject.flip = true;
    //     animal->gameObject.dest.x += animal->speed;
    // }

}

static void xAnimateAnimal(Animal *animal)
{
    int totalFrames = xGetAnimationLength(animal->state);

    animal->animationTimer += GetFrameTime();

    switch (animal->state)
    {
        case ANIMAL_IDLE:
        case ANIMAL_MOVING:
        default:

            while (animal->animationTimer >= animal->animationInterval)
            {
                animal->currentFrame++;
                animal->animationTimer -= animal->animationInterval;
            }

            if (animal->currentFrame >= totalFrames)
            {
                animal->currentFrame = 0;
            }
            
        break;
    }

    animal->gameObject.source.x = animal->currentFrame * animal->frameWidth;

    animal->gameObject.source.y = xGetAnimationLength(animal->state) * animal->frameHeight;

    animal->gameObject.source.width = animal->frameWidth;
    animal->gameObject.source.height = animal->frameHeight;

    // if (deltaTime >= animal->interval)
    // {
    //     animal->gameObject.source.x += 64;
    //     animal->gameObject.source.y += 64;

    //     if (animal->gameObject.source.x > 64)
    //         animal->gameObject.source.x = 0.0f;

    //     if (animal->gameObject.source.y > 64)
    //         animal->gameObject.source.y = 0.0f;

    //     if (animal->gameObject.flip)
    //         animal->gameObject.source.width *= -1;
    // }
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

    animal->gameObject.source = SPRITE_CHICKEN;
    animal->gameObject.dest = dest;

    animal->gameObject.collider = (xRectangle)
    {
        animal->gameObject.dest.x + 8,
        animal->gameObject.dest.y + 32,
        animal->gameObject.dest.width - 24,
        16
    };

    animal->gameObject.depth = animal->gameObject.collider.y + animal->gameObject.collider.height;

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

    animal->gameObject.source = SPRITE_SHEEP;
    animal->gameObject.dest = dest;

    animal->gameObject.collider = (xRectangle)
    {
        animal->gameObject.dest.x + 16,
        animal->gameObject.dest.y + 50,
        animal->gameObject.dest.width - 32,
        30
    };

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

    animal->gameObject.source = SPRITE_PIG;
    animal->gameObject.dest = dest;

    animal->gameObject.collider = (xRectangle)
    {
        animal->gameObject.dest.x + 16,
        animal->gameObject.dest.y + 50,
        animal->gameObject.dest.width - 32,
        30
    };

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

    animal->gameObject.source = SPRITE_COW;
    
    animal->gameObject.dest = dest;

    animal->gameObject.collider = (xRectangle)
    {
        animal->gameObject.dest.x + 16,
        animal->gameObject.dest.y + 50,
        animal->gameObject.dest.width - 32,
        30
    };

    animal->gameObject.depth = animal->gameObject.collider.y + animal->gameObject.collider.height;

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