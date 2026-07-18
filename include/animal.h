#ifndef ANIMAL_H
#define ANIMAL_H

#include "xEngine.h"

#define MAX_ANIMALS 32

typedef enum AnimalType
{
    ANIMAL_CHICKEN,
    ANIMAL_SHEEP,
    ANIMAL_PIG,
    ANIMAL_COW

} AnimalType;

typedef enum AnimalState
{
    ANIMAL_IDLE,
    ANIMAL_MOVING

} AnimalState;

typedef enum AnimalDirection
{
    ANIMAL_LEFT,
    ANIMAL_RIGHT

} AnimalDirection;

typedef struct Animal
{
    xGameObject gameObject;

    float interval;

    AnimalType type;

    AnimalState state;

    AnimalDirection direction;

    int speed;

} Animal;

typedef struct AnimalManager
{
    Animal animals[MAX_ANIMALS];
    int animalCount;

} AnimalManager;

void xUpdateAnimal(Animal *animal);

void xUnloadAnimal(Animal *animal);

void xSpawnChicken(AnimalManager *manager, xRectangle dest);

void xSpawnSheep(AnimalManager *manager, xRectangle dest);

void xSpawnPig(AnimalManager *manager, xRectangle dest);

void xSpawnCow(AnimalManager *manager, xRectangle dest);

#endif