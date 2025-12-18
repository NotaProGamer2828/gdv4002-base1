#pragma once

#include "GameObject2D.h"
#include <glm/glm.hpp>

class astroid : public GameObject2D {

private:
    
    float RotationSpeed = glm::radians(300.0f); // Rotation speed per second 

    glm::vec2 Direction;


public:
    astroid(glm::vec2 initPosition, float initOrientation, glm::vec2 initSize, GLuint initTextureID, glm::vec2 initDirection);

    void update(double tDelta) override;
};