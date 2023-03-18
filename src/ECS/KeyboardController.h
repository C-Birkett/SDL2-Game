#pragma once

#include "Game/Game.h"
#include "ECS.h"

class TransformComponent;
class SpriteComponent;

class KeyboardController : public Component
{
  public:
    TransformComponent* m_transform;
    SpriteComponent* m_sprite;

    void Init() override;
    void Update() override;
};
