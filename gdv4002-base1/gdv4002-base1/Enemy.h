#pragma once

#include "GameObject2D.h"
#include <glm/glm.hpp>

class astroid : public GameObject2D {

private:
    float		phaseAngle; // in radians
    float		phaseVelocity; // Angle change per second


    float RotationSpeed = glm::radians(300.0f); // Rotation speed per second 


public:
    astroid(glm::vec2 initPosition, float initOrientation, glm::vec2 initSize, GLuint initTextureID, float initialPhase, float initialPhaseVelocity);

    void update(double tDelta) override;
};