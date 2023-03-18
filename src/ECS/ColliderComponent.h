#pragma once

//#include "Game/Game.h"
#include "ECS.h"

#include <string.h>
#include <SDL2/SDL.h>

class TransformComponent;

class ColliderComponent : public Component
{
  public:
    ColliderComponent(std::string t);

    void Init() override;
    void Update() override;

    SDL_Rect GetCollider() const;
    std::string GetTag() const;

private:

    SDL_Rect m_collider;
    std::string m_tag;

    TransformComponent* m_transform;
};

inline SDL_Rect ColliderComponent::GetCollider() const
{
  return m_collider;
}

inline std::string ColliderComponent::GetTag() const
{
  return m_tag;
}
