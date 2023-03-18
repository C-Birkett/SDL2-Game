#pragma once

#include "ECS.h"
#include "AnimationComponent.h"
#include "TextureManager/TextureManager.h"

#include <SDL2/SDL.h>
#include <vector>

#define TILESET_WIDTH 5

enum anims
{
  IdleAnim,
  WalkAnim,
};

class TransformComponent;

typedef struct TileSet
{
    std::string name;
    const char* path;
}TileSet;

class SpriteComponent : public Component
{
  private:

    TransformComponent* m_transform;
    SDL_Texture* m_texture;
    SDL_Rect m_srcRect, m_destRect;

    //tiles
    TileSet* m_tileSet;
    int m_tileID = -1;

    //animation
    bool m_isAnimated = false;
    int m_animFrames = 0;
    int m_animSpeed = 250;

  public:

    int m_animIndex = 0;
    std::vector<Animation> m_animations;

    SDL_RendererFlip m_doSpriteFlip = SDL_FLIP_NONE;

    SpriteComponent();

    SpriteComponent(const char* path)
    {
      SetTex(path);
    }

    //animated
    SpriteComponent(const char* path, bool isAnimated);

    //tileset
    SpriteComponent(TileSet* tSet, int id);

    ~SpriteComponent()
    {
      SDL_DestroyTexture(m_texture);
    }

    void SetTex(const char* path);

    void Init() override;
    void Update() override;
    void Draw() override;

    void PlayAnimation(anims animName);
};

inline void SpriteComponent::SetTex(const char* path)
{
    m_texture = TextureManager::LoadTexture(path);
}

inline void SpriteComponent::Draw()
{
      TextureManager::Draw(m_texture, m_srcRect, m_destRect, m_doSpriteFlip);
}
