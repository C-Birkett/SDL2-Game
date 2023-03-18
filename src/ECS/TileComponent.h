#pragma once

#include "ECS.h"
#include <SDL2/SDL.h>
#include <stdio.h>

#define TILESET_SCALE 4

class TileSet;
class TransformComponent;
class SpriteComponent;

class TileComponent : public Component
{
  public:
    TransformComponent* m_transform;
    SpriteComponent* m_sprite;

    SDL_Rect m_tileRect;
    TileSet* m_tileSet;
    int m_tileID;

    TileComponent(){};

    TileComponent(int x, int y, int w, int h, TileSet* tSet, int id);

    ~TileComponent(){};

  void Init() override;
};
