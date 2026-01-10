#include "Engine.h"
#include "Keys.h"
#include <bitset>
#include <random>
#include "Player.h"  
#include "Enemy.h"

// --- (Global varaiable) ---
const float pi = 3.142f;

// Function prototypes
void myKeyboardHandler(GLFWwindow* window, int key, int scancode, int action, int mods);

//Controls of Ship
std::bitset<5> keys{ 0x0 };

int main(void) {

    // Initialises the engine (create window, setup OpenGL backend)
    int initResult = engineInit("GDV4002 - Applied Maths for Games", 512, 512, 5);

    // If the engine initialisation failed report error and exit
    if (initResult != 0) {

        printf("Cannot setup game window!!!\n");
        return initResult; // Exit if setup failed
    }

    // Setup rendering properties (enable blending)
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDepthFunc(GL_ALWAYS);

    // --- (Random number setup) ---
    std::mt19937 gen;
    std::uniform_real_distribution<float> normDist, normX, normY, normScale;

    std::random_device rd;
    gen = std::mt19937(rd());
    normDist = std::uniform_real_distribution<float>(-1.0f, 1.0f);
    normX = std::uniform_real_distribution<float>(-getViewplaneWidth() / 2.0f, getViewplaneWidth() / 2.0f);
    normY = std::uniform_real_distribution<float>(-getViewplaneHeight() / 2.0f, getViewplaneHeight() / 2.0f);

    // --- (Setup game scene objects here) ---
    GLuint playerTexture = loadTexture("Resources\\Textures\\player1_ship.png",TextureProperties::NearestFilterTexture());
    Player* mainPlayer = new Player(glm::vec2(-1.5f, 0.0f), 0.0f, glm::vec2(0.5f, 0.5f), playerTexture, 1.0f);
    addObject("player1", mainPlayer);

    // --- (Asteroid Set up) ---
    GLuint AsteroidTexture = loadTexture("Resources\\Textures\\Asteroid.png", TextureProperties::NearestFilterTexture());

    // Random speed distribution
    std::uniform_real_distribution<float> speedDist(0.5f, 2.0f);
    for (int i = 0; i < 6; i++)
    {
        float px = normX(gen);
        float py = normY(gen);

        // Random direction
        float dx = normDist(gen);
        float dy = normDist(gen);
        glm::vec2 dir = glm::normalize(glm::vec2(dx, dy));

        // Random speed
        float speed = speedDist(gen);

        // Final velocity
        glm::vec2 velocity = dir * speed;
        Asteroid* a = new Asteroid(glm::vec2(px, py), 0.0f, glm::vec2(0.75f, 0.75f), AsteroidTexture, velocity);
        addObject("astroid", a);
    }

    // Setup game sceen object here
    setKeyboardHandler(myKeyboardHandler);

    // Outputs name and amount of objects (Useful for performance check)
    listGameObjectKeys();
    listObjectCounts();

    // Hides axis lines on screen
    hideAxisLines();

    // Handles update and render calls
    engineMainLoop();

    // Clean up engine resources when program closes
    engineShutdown();

    // Return success :)
    return 0;
}

// --- (keyboard Input Repsonce) ---
void myKeyboardHandler(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    // Check if a key is being pressed
    if (action == GLFW_PRESS)
    {
        // Checks which key is being pressed
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
        case GLFW_KEY_SPACE:
            keys[Key::SPACE] = true;
            printf("SPACE Pressed\n");
            break;
        }
    }
    if (action == GLFW_RELEASE)
    {
        // Handle key release events
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
        case GLFW_KEY_SPACE:
            keys[Key::SPACE] = false;
            printf("SPACE Released\n");
            break;
        }
    }
}

