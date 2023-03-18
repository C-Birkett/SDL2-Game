#include "GameObject.h"
#include "TextureManager/TextureManager.h"

GameObject::GameObject(const char* texturesheet, int x, int y)
{
  objTexture = TextureManager::LoadTexture(texturesheet);

  xpos = x;
  ypos = y;
}

void GameObject::Update()
{
  xpos++;

  srcRect.h = 16;
  srcRect.w = 16;
  srcRect.x = 0;
  srcRect.y = 0;

  destRect.x = xpos;
  destRect.y = ypos;
  destRect.h = srcRect.h * TEXTURE_SCALE;
  destRect.w = srcRect.w * TEXTURE_SCALE;
}

void GameObject::Render()
{
  SDL_RenderCopy(Game::renderer, objTexture, &srcRect, &destRect);
}
