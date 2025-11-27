#include "Player.h"
#include "Keys.h"
#include <bitset>
#include "Engine.h"

extern std::bitset<5> keys;

Player::Player(glm::vec2 initPosition, float initOrientation, glm::vec2 initSize, GLuint initTextureID, float mass) : GameObject2D(initPosition, initOrientation, initSize, initTextureID) {

    this->mass = mass;

    velocity = glm::vec2(0.0f, 0.0f); // default to 0 velocity
}



void Player::update(double tDelta) {

    // Unlike our myUpdate function, we're already 'in' the player object, so no need to call getObject as we did before :)

    static float playerSpeed = 1.0f; // distance per second

    GameObject2D* player = getObject("player1");

    if (keys.test(Key::W) == true) {

        player->position.y += playerSpeed * (float)tDelta;

    }
    if (keys.test(Key::S) == true) {

        player->position.y -= playerSpeed * (float)tDelta;
    }

    if (keys.test(Key::A) == true) {

        player->orientation += glm::radians(90.0f) * static_cast<float>(tDelta);
    }
    if (keys.test(Key::D) == true) {

        player->orientation -= glm::radians(90.0f) * static_cast<float>(tDelta);

    }
}
