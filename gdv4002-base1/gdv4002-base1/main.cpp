#include "Engine.h"

// Function prototypes


int main(void) {

	// Initialise the engine (create window, setup OpenGL backend)
	int initResult = engineInit("GDV4002 - Applied Maths for Games", 1024, 1024);

	// If the engine initialisation failed report error and exit
	if (initResult != 0) {

		printf("Cannot setup game window!!!\n");
		return initResult; // exit if setup failed
	}

	//
	// Setup game scene objects here
	//
	const float pi = 3.142f;
	
	addObject("player1", glm::vec2(1.0f, 1.0f), glm::radians(45.0f), glm::vec2(0.5f, 1.0f), "Resources\\Textures\\player1_ship.png", TextureProperties::NearestFilterTexture());
	
	GameObject2D* player1Object = getObject("player1");
	if (player1Object != nullptr) {

		// update player1 here

	}
	
	addObject("player2");
	






	// Enter main loop - this handles update and render calls
	engineMainLoop();

	// When we quit (close window for example), clean up engine resources
	engineShutdown();

	// return success :)
	return 0;
}


