#pragma once

#include "Game/Game.h"

#define TEXTURE_SCALE 4

class TextureManager{

  public:
    static SDL_Texture* LoadTexture(const char* filename);
    static void Draw(SDL_Texture* tex, SDL_Rect src, SDL_Rect dest, SDL_RendererFlip flip);
};
