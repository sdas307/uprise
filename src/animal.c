#include "animal.h"
#include "config.h"
#include "assets.h"

#include <stdio.h>

/* ---------- Signatures ----------*/

static void xMoveAnimal(Animal *animal);

static void xInitAnimal(Animal *animal);

static void xAnimateAnimal(Animal *animal);

static float deltaTime = 0.0f;
static float randomInterval = 0.0f;
static float r = 0.0f;


/* ---------- Implementation ----------*/

static void xInitAnimal(Animal *animal)
{
    animal->interval = 0.10f;

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
    int randomValue = GetRandomValue(0, 3);
    r += GetFrameTime();

    if (r >= randomValue)
    {
        animal->state = GetRandomValue(ANIMAL_IDLE, ANIMAL_MOVING);
    }

    if (animal->state == ANIMAL_MOVING)
    {
        animal->direction = GetRandomValue(ANIMAL_LEFT, ANIMAL_RIGHT);
    }
    
    if (animal->direction == ANIMAL_LEFT)
        animal->gameObject.dest.x -= animal->speed;

    if (animal->direction == ANIMAL_RIGHT)
        animal->gameObject.dest.x += animal->speed;

}

static void xAnimateAnimal(Animal *animal)
{
    deltaTime += GetFrameTime();

    if (deltaTime >= animal->interval)
    {
        animal->gameObject.source.x += 64;
        animal->gameObject.source.y += 64;
    }

    deltaTime -= animal->interval;
}

void xUnloadAnimal(Animal *animal)
{
    UnloadTexture(animal->gameObject.texture);
}

void xSpawnChicken(AnimalManager *manager, xRectangle dest)
{
    if (manager->animalCount >= MAX_ANIMALS)
        return;

    Animal *animal = &manager->animals[manager->animalCount++];

    xInitAnimal(animal);

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
    if (manager->animalCount >= MAX_ANIMALS)
        return;

    Animal *animal = &manager->animals[manager->animalCount++];

    xInitAnimal(animal);

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
    if (manager->animalCount >= MAX_ANIMALS)
        return;

    Animal *animal = &manager->animals[manager->animalCount++];

    xInitAnimal(animal);

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
    if (manager->animalCount >= MAX_ANIMALS)
        return;

    // Create new animal
    Animal *animal = &manager->animals[manager->animalCount++];

    xInitAnimal(animal);

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