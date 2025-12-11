#include "Engine.h"
#include "Keys.h"
#include <bitset>
#include "Player.h"  
#include "Enemy.h"

// Global varaiable
const float pi = 3.142f;

//Gravity
glm::vec2 gravity = glm::vec2(0.0f, 0.0f);

// Function prototypes
void myUpdate(GLFWwindow* window, double tDelta);
void myKeyboardHandler(GLFWwindow* window, int key, int scancode, int action, int mods);

//Controls of Ship
std::bitset<5> keys{ 0x0 };

int main(void) {

	//Initialise the engine (create window, setup OpenGL backend)
	int initResult = engineInit("GDV4002 - Applied Maths for Games", 512, 512, 5);

	//If the engine initialisation failed report error and exit
	if (initResult != 0) {

		printf("Cannot setup game window!!!\n");
		return initResult; // exit if setup failed
	}

	//Setup game scene objects here
    GLuint playerTexture = loadTexture("Resources\\Textures\\player1_ship.png",TextureProperties::NearestFilterTexture());
    Player* mainPlayer = new Player(glm::vec2(-1.5f, 0.0f), 0.0f, glm::vec2(0.5f, 0.5f), playerTexture, 1.0f);
    addObject("player1", mainPlayer);

    addObject("bullet", glm::vec2(1.0f, 1.0f), 0.0f, glm::vec2(0.5f, 0.5f), "Resources\\Textures\\Bullet.png", TextureProperties::NearestFilterTexture());

    GLuint asteroidTexture = loadTexture("Resources\\Textures\\Astroid.png", TextureProperties::NearestFilterTexture());
    astroid* astroid1 = new astroid(glm::vec2(0.0f, 0.0f), 0.0f, glm::vec2(0.75f, 0.75f), asteroidTexture, 0.0f, glm::radians(90.0f));
    addObject("astroid", astroid1);
    astroid* astroid2 = new astroid(glm::vec2(1.0f, 0.0f), 0.0f, glm::vec2(0.75f, 0.75f), asteroidTexture, 0.0f, glm::radians(90.0f));
    addObject("astroid", astroid2);
    astroid* astroid3 = new astroid(glm::vec2(2.0f, 0.0f), 0.0f, glm::vec2(0.75f, 0.75f), asteroidTexture, 0.0f, glm::radians(90.0f));
    addObject("astroid", astroid3);

	addObject("alien", glm::vec2(0.0f, 0.0f), glm::radians(0.0f), glm::vec2(0.50f, 0.50f), "Resources\\Textures\\Alien.png", TextureProperties::NearestFilterTexture());
	
	//setup game sceen object here
	setKeyboardHandler(myKeyboardHandler);

	// Outputs name and amount of objects (Useful for performance check)
	listGameObjectKeys();
	listObjectCounts();

	//Enter main loop - this handles update and render calls
	engineMainLoop();

	//When we quit (close window for example), clean up engine resources
	engineShutdown();

	//Return success :)
	return 0;
}

//Astoid movement
float astroidPhase[3] = { 0.0f, 0.0f, 0.0f };
float astroidPhaseVelocity[3] = { glm::radians(90.0f),  glm::radians(90.0f), glm::radians(90.0f) };

//Calls myUpdate function
void myUpdate(GLFWwindow* window, double tDelta) {

    GameObject2D* player = getObject("player1");

	//Astroid collection
	GameObjectCollection astroid = getObjectCollection("astroid");

	for (int i = 0; i < astroid.objectCount; i++) {
		astroid.objectArray[i]->position.y = sinf(astroidPhase[i]); // assume phase stored in radians so no conversion needed
		astroidPhase[i] += astroidPhaseVelocity[i] * tDelta;
	}
}

void myKeyboardHandler(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	//Check if the key was just pressed
	if (action == GLFW_PRESS) {
	//Now check which key was pressed...
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
        //Handle key release events
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

