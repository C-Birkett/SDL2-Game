#include "TextureManager.h"

#include <SDL2/SDL_image.h>
//#include <SDL2/SDL_surface.h>

SDL_Texture* TextureManager::LoadTexture(const char* filename)
{
  SDL_Texture* tex = nullptr;
  SDL_Surface* tempSurface = IMG_Load(filename);
  if(tempSurface == NULL){
    printf("unable to load image %s! SDL: %s\n", "test_image.bmp", SDL_GetError());
  }
  else
  {
    tex = SDL_CreateTextureFromSurface(Game::renderer, tempSurface);
    SDL_FreeSurface(tempSurface);
  }
  
  return tex;
}

void TextureManager::Draw(SDL_Texture* tex, SDL_Rect src, SDL_Rect dest, SDL_RendererFlip flip)
{
  //SDL_RenderCopy(Game::renderer, tex, &src, &dest);
  SDL_RenderCopyEx(Game::renderer, tex, &src, &dest, 0.0, NULL, flip);
}
