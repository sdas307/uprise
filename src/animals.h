#ifndef ANIMALS_H
#define ANIMALS_H

#include "xEngine.h"

typedef enum AnimalState
{
    ANIMAL_IDLE,
    ANIMAL_MOVING

} AnimalState;

typedef enum AnimalDirection
{
    ANIMAL_FRONT,
    ANIMAL_BACK,
    ANIMAL_LEFT,
    ANIMAL_RIGHT

} AnimalDirection;

typedef struct Animal
{
    xGameObject gameObject;

    float interval;

    AnimalState state;

    AnimalDirection direction;

    int speed;

} Animal;

void xInitAnimal(Animal *animal);

void xUpdateAnimal(Animal *animal);

void xMoveAnimal(Animal *animal);

void xUnloadAnimal(Animal *animal);

#endif