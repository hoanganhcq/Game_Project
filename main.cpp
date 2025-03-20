#include <iostream>
#include "GameLoop.h"
using namespace std;

GameLoop* g = new GameLoop();

int main(int argc, char** argv)
{
    double first;
    double last = 0;

    g->Initialize();
    while (g->getGameState())
    {
        g->Event();
        g->Update();
        g->Render();

        first = SDL_GetTicks();
        if (first - last < 16.7)
        {
            SDL_Delay(static_cast<Uint32>(16.7 - (first - last))); // 60FPS ~ 16.67 ms per frame
        }
        last = first;
    }
    g->Clear();
    delete g;
    return 0;
}