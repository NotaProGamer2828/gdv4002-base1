#include "Emitter.h"
#include "Engine.h"
#include "Enemy.h"

using namespace std;


Emitter::Emitter(glm::vec2 initPosition, glm::vec2 initSize, float emitTimeInterval) : GameObject2D(initPosition, 0.0f, initSize, 0) 
{
   /* this->emitTimeInterval = emitTimeInterval;
    emitCounter = emitTimeInterval;
    
    particleNumber = 0;*/

}

