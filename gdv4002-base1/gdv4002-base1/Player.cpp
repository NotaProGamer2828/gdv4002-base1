#include "Player.h"
#include "Keys.h"
#include <bitset>
#include "Engine.h"

extern std::bitset<5> keys;
extern glm::vec2 gravity;

Player::Player(glm::vec2 initPosition, float initOrientation, glm::vec2 initSize, GLuint initTextureID, float mass) : GameObject2D(initPosition, initOrientation, initSize, initTextureID) {

    this->mass = mass;

    velocity = glm::vec2(0.0f, 0.0f); // default to 0 velocity
}

float temp = 0.0f;
float maxSpeed = 0.05f;

void Player::update(double tDelta) 
{
    glm::vec2 F;
    const float thrust = 0.03f;
    //cyrrnt speed

    // 1. accumulate forces
    if (keys.test(Key::W) == true) 
    {
        temp += thrust;
    }
    if (keys.test(Key::S) == true) 
    {
        temp -= thrust;
    }
    if (keys.test(Key::A) == true) 
    {
        orientation += glm::radians(180.0f) * tDelta;
    }
    if (keys.test(Key::D) == true) 
    {
        orientation -= glm::radians(180.0f) * tDelta;
    }
    
    F = glm::vec2(temp * cos(orientation) * (float)tDelta, temp * sin(orientation) * (float)tDelta);

    F += gravity;
    
    // Checl if F is larger than max speed
    if (glm::length(F) > maxSpeed)
    {
        // Get the direction direction vector of the force
        F = glm::normalize(F);

        // Scale that direction to our max speed
        F *= maxSpeed;
    }


    // add impulse force
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


    // Add that to the postion
    position += F;

}

