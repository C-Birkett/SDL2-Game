#include "Game/Game.h"

#define SCREEN_WIDTH   1280
#define SCREEN_HEIGHT  720

int main(int argc, char* argv[]) 
{
    const int FPS = 60;
    const int frameDelay = 1000/FPS;

    Uint32 frameStart;
    int frameTime;

    Game* game = new Game();
    game->init("GameWindow", SCREEN_WIDTH, SCREEN_HEIGHT, false);

    while (game->running())
    {
        frameStart = SDL_GetTicks();

        game->handleEvents();
        game->update();
        game->render();

        frameTime = SDL_GetTicks() - frameStart;

        if(frameDelay > frameTime)
        {
        SDL_Delay(frameDelay - frameTime);
        }
    }

    game->clean();
    return 0;
}
