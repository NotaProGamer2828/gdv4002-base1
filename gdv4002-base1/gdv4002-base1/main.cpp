#include "Engine.h"
#include "Keys.h"
#include <bitset>
#include "Player.h"  
#include "Enemy.h"

// Global varaiable
const float pi = 3.142f;

// Function prototypes
void myUpdate(GLFWwindow* window, double tDelta);
void myKeyboardHandler(GLFWwindow* window, int key, int scancode, int action, int mods);

std::bitset<5> keys{ 0x0 };

int main(void) {

	// Initialise the engine (create window, setup OpenGL backend)
	int initResult = engineInit("GDV4002 - Applied Maths for Games", 1024, 1024, 5);

	// If the engine initialisation failed report error and exit
	if (initResult != 0) {

		printf("Cannot setup game window!!!\n");
		return initResult; // exit if setup failed
	}

	// Setup game scene objects here
	
    GLuint playerTexture = loadTexture("Resources\\Textures\\player1_ship.png",TextureProperties::NearestFilterTexture());
    Player* mainPlayer = new Player(glm::vec2(-1.5f, 0.0f), 0.0f, glm::vec2(0.5f, 0.5f), playerTexture, 1.0f);
    addObject("player1", mainPlayer);
    addObject("bullet", glm::vec2(1.0f, 1.0f), 0.0f, glm::vec2(0.5f, 0.5f), "Resources\\Textures\\Bullet.png", TextureProperties::NearestFilterTexture());


	addObject("astroid", glm::vec2(0.0f, 0.0f), 0.0f, glm::vec2(0.75f, 0.75f), "Resources\\Textures\\Astroid.png", TextureProperties::NearestFilterTexture());
	addObject("astroid", glm::vec2(1.0f, 0.0f), 0.0f, glm::vec2(0.75f, 0.75f), "Resources\\Textures\\Astroid.png", TextureProperties::NearestFilterTexture());
	addObject("astroid", glm::vec2(2.0f, 0.0f), 0.0f, glm::vec2(0.75f, 0.75f), "Resources\\Textures\\Astroid.png", TextureProperties::NearestFilterTexture());

	addObject("alien", glm::vec2(0.0f, 0.0f), glm::radians(0.0f), glm::vec2(0.50f, 0.50f), "Resources\\Textures\\Alien.png", TextureProperties::NearestFilterTexture());

	GameObject2D* player1Object = getObject("player1");
	if (player1Object != nullptr) {
		// update player1 here
		player1Object->position = glm::vec2(-1.0f, 1.0f);
		player1Object->textureID = loadTexture("Resources\\Textures\\player1_ship.png");
		
	}
	
	//setup game sceen object here
	setUpdateFunction(myUpdate);
	void key_callback(GLFWwindow * window, int key, int scancode, int action, int mods);

	setUpdateFunction(myUpdate);
	setKeyboardHandler(myKeyboardHandler);

	// Outputs name and amount of objects (Useful for performance check)
	listGameObjectKeys();
	listObjectCounts();


	// Enter main loop - this handles update and render calls
	engineMainLoop();

	// When we quit (close window for example), clean up engine resources
	engineShutdown();

	// return success :)
	return 0;
}

//astoid movement
float astroidPhase[3] = { 0.0f, 0.0f, 0.0f };
float astroidPhaseVelocity[3] = { glm::radians(90.0f),  glm::radians(90.0f),
 glm::radians(90.0f) };


// Calls myUpdate function

void myUpdate(GLFWwindow* window, double tDelta) {

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

// wraps game to make player stay witin the screen
if (player->position.y > getViewplaneHeight() / 2.0f)
    player->position.y = -getViewplaneHeight() / 2.0f;
if (player->position.y < -getViewplaneHeight() / 2.0f)
    player->position.y = getViewplaneHeight() / 2.0f;

if (player->position.x > getViewplaneHeight() / 2.0f)
player->position.x = -getViewplaneHeight() / 2.0f;
if (player->position.x < -getViewplaneHeight() / 2.0f)
    player->position.x = getViewplaneHeight() / 2.0f;

	//astroid collection
	GameObjectCollection astroid = getObjectCollection("astroid");
	astroid.objectArray[0]->position.y = sinf(astroidPhase[0]); // assume phase stored in radians so no conversion needed
	
	astroidPhase[1] += astroidPhaseVelocity[1] * tDelta;

	for (int i = 0; i < astroid.objectCount; i++) {

		astroid.objectArray[i]->position.y = sinf(astroidPhase[i]); // assume phase stored in radians so no conversion needed

		astroidPhase[i] += astroidPhaseVelocity[i] * tDelta;
	}


	//updates angles
	float anglesPerSecond = glm::radians(45.0f);

	//updates player1 rotation and speed 
	float playerVelocity = 2.0f;
	float player1RotationSpeed = glm::radians(300.0f);

	GameObject2D* astroidObject = getObject("astroid");
	if (astroidObject != nullptr) {
		astroidObject->orientation += player1RotationSpeed * tDelta;
	}
  
}

void myKeyboardHandler(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	// Check if the key was just pressed
	if (action == GLFW_PRESS) {
		// now check which key was pressed...
		switch (key)
		{
        case GLFW_KEY_W:
            keys[Key::W] = true;
            printf("w Pressed\n");
            break;
		case GLFW_KEY_A:
			keys[Key::A] = true;
			printf("a Pressed\n");
			break;
		case GLFW_KEY_S:
			keys[Key::S] = true;
			printf("s Pressed\n");
			break;
		case GLFW_KEY_D:
			keys[Key::D] = true;
			printf("d Pressed\n");
			break;
		}
	}
    if (action == GLFW_RELEASE) {
        // handle key release events
        switch (key)
        {
        case GLFW_KEY_W:
            keys[Key::W] = false;
            printf("w Released\n");
            break;
		case GLFW_KEY_A:
			keys[Key::A] = false;
			printf("a Released\n");
			break;
		case GLFW_KEY_S:
			keys[Key::S] = false;
			printf("s Released\n");
			break;
		case GLFW_KEY_D:
			keys[Key::D] = false;
			printf("d Released\n");
			break;
        }
    }
}

