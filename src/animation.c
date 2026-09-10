#include "animation.h"
#include <stdio.h>

/* ---------- Signatures ---------- */

static void Animate(xGameObject *object, float dt);

/* ---------- ---------- ---------- */

void xUpdateAnimation(World *world, float dt)
{
    for (int i = 0; i < world->entityCount; i++)
    {
        Animate(&world->entities[i].gameObject, dt);
    }
}

static void Animate(xGameObject *object, float dt)
{
    Animation *animation = &object->animation;

    if (!animation->active)
        return;
    
    animation->timer += dt;

    if (animation->timer >= animation->frameTime)
    {
        animation->timer -= animation->frameTime;

        animation->currentFrame++;

        if (animation->currentFrame >= animation->frameCount)
            animation->currentFrame = 0;

        if (!animation->frameCount == 0)
            object->source = animation->frames[animation->currentFrame];
    }
}