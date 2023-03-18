#pragma once

#include <stdio.h>
#include <iostream>
#include <cmath>
#include <math.h>
#include <vector>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <SDL2/SDL_error.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_render.h>

class ColliderComponent;
struct TileSet;

class Game{

  public:
    Game();
    ~Game();

    void init(const char* title, int width, int height, bool fullscreen);

    void handleEvents();
    void update();
    bool running() {return isRunning;}
    void render();
    void clean();

    static void AddTile(int x, int y, TileSet* tileSet, int ID);

    static SDL_Renderer* renderer;
    static SDL_Event event;
    static bool isRunning;
    static std::vector<ColliderComponent*> colliders;

  private:
    int cnt = 0;
    SDL_Window* window;
};
