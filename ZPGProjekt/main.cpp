#include "Engine.h"

int main()
{
    Engine* engine = new Engine();
    engine->start();
    delete engine;
}

