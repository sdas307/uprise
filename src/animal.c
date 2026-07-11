#include "animal.h"
#include "config.h"
#include "assets.h"

/* ---------- Signatures ----------*/

static void xMoveAnimal(Animal *animal);

static void xInitAnimal(Animal *animal);


/* ---------- Implementation ----------*/

static void xInitAnimal(Animal *animal)
{
    animal->interval = 0.10f;

    animal->state = ANIMAL_IDLE;
    animal->direction = ANIMAL_LEFT;

    animal->gameObject.active = true;
}

void xUpdateAnimal(Animal *animal)
{
    xMoveAnimal(animal);
}

static void xMoveAnimal(Animal *animal)
{

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
        animal->gameObject.dest.x + 16,
        animal->gameObject.dest.y + 50,
        animal->gameObject.dest.width - 32,
        30
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