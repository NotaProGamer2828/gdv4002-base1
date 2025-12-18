
#include "Enemy.h"
#include "Engine.h"

astroid::astroid(
    glm::vec2 initPosition,
    float initOrientation,
    glm::vec2 initSize,
    GLuint initTextureID,
    glm::vec2 initDirection)
    : GameObject2D(initPosition, initOrientation, initSize, initTextureID) {

    Direction = initDirection;
}

void astroid::update(double tDelta) {

    // Set position
    position = position + (Direction * (float)tDelta);

    //rotates astroid
    orientation += RotationSpeed * tDelta;

    // Add Wrap so that Player stays within window
    if (position.y < -getViewplaneHeight() / 2.0f)
    {
        position.y = getViewplaneHeight() / 2.0f;
    }

    else if (position.y > getViewplaneHeight() / 2.0f)
    {
        position.y = -getViewplaneHeight() / 2.0f;
    }

    if (position.x < -getViewplaneHeight() / 2.0f)
    {
        position.x = getViewplaneHeight() / 2.0f;
    }

    else if (position.x > getViewplaneHeight() / 2.0f)
    {
        position.x = -getViewplaneHeight() / 2.0f;
    }
  }

   
