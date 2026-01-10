#include "Bullet.h"
#include "Engine.h"

Bullet::Bullet(glm::vec2 initPosition,float initOrientation,glm::vec2 initSize,GLuint initTextureID,glm::vec2 initDirection)
    : GameObject2D(initPosition, initOrientation, initSize, initTextureID)
{
    Direction = initDirection;
}

void Bullet::update(double tDelta)
{
    // Move bullet
    position += Direction * (float)tDelta;

    // Screen bounds
    float halfH = getViewplaneHeight() / 2.0f;
    float halfW = getViewplaneWidth() / 2.0f;

    // Mark for deletion if bullet is off screen
    if (!this->pendingDelete &&
        (position.x < -halfW || position.x > halfW ||
         position.y < -halfH || position.y > halfH))
    {
        this->pendingDelete = true;
        printf("Bullet is deleted\n");
    }
}


