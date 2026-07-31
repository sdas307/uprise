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
    ANIMAL_RIGHT,
    ANIMAL_UP,
    ANIMAL_DOWN

} AnimalDirection;

typedef struct Animal
{
    xGameObject gameObject;

    int moveX;
    int moveY;

    float animIdleInterval;
    float animMovingInterval;
    float animTimer;
    int currentFrame;
    int frameWidth;
    int frameHeight;

    AnimalType type;

    AnimalState state;

    AnimalDirection direction;

    float randomInterval;           // The duration of the state.
    int randomStateTimer;           // Random time value from 0 to max state timer.
    int stateTimerMax;              // Max value for state timer.

    int hp;
    int speed;

} Animal;

typedef struct AnimalManager
{
    Animal animals[MAX_ANIMALS];
    int animalCount;

} AnimalManager;

struct World;
typedef struct World World;

void xUpdateAnimal(Animal *animal, World *world);

void xUnloadAnimal(Animal *animal);

void xSpawnChicken(AnimalManager *manager, xRectangle dest);

void xSpawnSheep(AnimalManager *manager, xRectangle dest);

void xSpawnPig(AnimalManager *manager, xRectangle dest);

void xSpawnCow(AnimalManager *manager, xRectangle dest);

#endif