#include "animals.h"
#include "config.h"

void xInitAnimal(Animal *animal)
{
    animal->gameObject.texture = LoadTexture(PATH_COW_SHEET);
    animal->interval = 0.10f;

    animal->gameObject.source = (xRectangle) {20, 22, 64*2 - 30, 64*2 - 42};

    animal->gameObject.dest = (xRectangle) {64*8, 64*6, 64*2 - 24, 64*2 - 42};
    
    animal->gameObject.collider = (xRectangle)
    {
        animal->gameObject.dest.x + 16,
        animal->gameObject.dest.y + 50,
        animal->gameObject.dest.width - 32,
        30
    };

    animal->gameObject.depth = animal->gameObject.collider.y + animal->gameObject.collider.height;

    animal->state = ANIMAL_IDLE;
    animal->direction = ANIMAL_FRONT;

    animal->gameObject.active = true;
    animal->gameObject.flip = false;

    animal->speed = 2;
}

void xUpdateAnimal(Animal *animal)
{
    xMoveAnimal(animal);
}

void xMoveAnimal(Animal *animal)
{
    xRectangle animalMoveArea = {64*8, 64*6, 64*5, 64*4};

    animal->state = ANIMAL_MOVING;

    animal->direction = ANIMAL_RIGHT;

    if (animal->gameObject.dest.x < (animalMoveArea.x + animalMoveArea.width))
    {
        animal->gameObject.dest.x += animal->speed;
        animal->gameObject.collider.x += animal->speed;
    }
}