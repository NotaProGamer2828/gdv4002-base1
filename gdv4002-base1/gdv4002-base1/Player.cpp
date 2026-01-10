#include "Player.h"
#include "Bullet.h"
#include "Keys.h"
#include <bitset>
#include "Engine.h"

extern std::bitset<5> keys;

Player::Player(glm::vec2 initPosition, float initOrientation, glm::vec2 initSize, GLuint initTextureID, float mass) : GameObject2D(initPosition, initOrientation, initSize, initTextureID)
{
    this->mass = mass;
    velocity = glm::vec2(0.0f, 0.0f);
}

// --- (Player physics) ---
float temp = 0.0f; // Tempory speed of player
float maxSpeed = 0.02; // Stops player from going too fast in the game
bool prevSpace = false; // One-shot fire flag to stop bullets being shot continuously when holding the space key

void Player::update(double tDelta)
{
    glm::vec2 F;
    const float thrust = 0.008f; // acceleration speed of player when moving

    // --- (Movement input) ---
    if (keys.test(Key::W)) temp += thrust; // Forward input
    if (keys.test(Key::S)) temp -= thrust; // Backward input

    if (keys.test(Key::A))
        orientation += glm::radians(270.0f) * tDelta; // Rotate left input
    if (keys.test(Key::D))
        orientation -= glm::radians(270.0f) * tDelta; // Rotate right input

    // --- (Bullet input) ---
    if (keys.test(Key::SPACE) && !prevSpace)
    {
        GLuint bulletTexture = loadTexture("Resources\\Textures\\Bullet.png", TextureProperties::NearestFilterTexture());

        glm::vec2 forward = glm::vec2(cosf(orientation), sinf(orientation));
        glm::vec2 bulletPos = position + forward * 0.25f; // Spawns bullet in front of ship
        glm::vec2 bulletVel = forward * 5.0f; // Bullet speed

        Bullet* bulletShot = new Bullet(bulletPos, orientation, glm::vec2(0.5f, 0.5f), bulletTexture, bulletVel);
        addObject("Bullet", bulletShot);
    }
    prevSpace = keys.test(Key::SPACE); // This stops the bullets from being held down from the space key

    // --- (Movement physics) ---
    F = glm::vec2(temp * cos(orientation) * (float)tDelta, temp * sin(orientation) * (float)tDelta);

    // --- (Clamp speed/ Maxinum Speed) ---
    if (glm::length(F) > maxSpeed) // Checks if player is faster than max speed
    F = glm::normalize(F) * maxSpeed; // Keeps the player at max speed once they are at the max value or higher

    // --- (Screen wrap) ---
    float halfH = getViewplaneHeight() / 2.0f; // This can be used for both horizontal and vertical values of the screen optimising the original code significantly 
    if (position.y < -halfH) position.y = halfH;
    else if (position.y > halfH) position.y = -halfH;
    if (position.x < -halfH) position.x = halfH;
    else if (position.x > halfH) position.x = -halfH;

    // --- (Apply movement) ---
    position += F; // This is what allows the player to move once all of teh calculations are made
}



