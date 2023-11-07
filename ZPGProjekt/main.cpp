#include "Engine.h"
#include <string> 

int main()
{
    Engine* engine = new Engine();
    engine->start();
    delete engine;
}

