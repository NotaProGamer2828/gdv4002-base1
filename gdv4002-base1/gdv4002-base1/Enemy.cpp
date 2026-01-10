
#include "Enemy.h"
#include "Engine.h"


Asteroid::Asteroid(
    glm::vec2 initPosition,float initOrientation,glm::vec2 initSize,GLuint initTextureID,glm::vec2 initDirection): GameObject2D(initPosition, initOrientation, initSize, initTextureID)

{
    Direction = initDirection;
}

void Asteroid::update(double tDelta) {

    // Moves asteroid
    position += Direction * (float)tDelta;

    // Rotation based on speed
    float speed = glm::length(Direction);
    float rotationFactor = 4.0f; // adjust for desired spin intensity
    orientation += speed * rotationFactor * tDelta; // rotates asteroid

    // Screen wrap
    float halfH = getViewplaneHeight() / 2.0f; // This can be used for both horizontal and vertical values of the screen optimising the original code significantly
    if (position.y < -halfH) position.y = halfH;
    else if (position.y > halfH) position.y = -halfH;
    if (position.x < -halfH) position.x = halfH;
    else if (position.x > halfH) position.x = -halfH;
}


