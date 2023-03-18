#pragma once

#include "ECS.h"
#include "Vector2D/Vector2D.h"

class TransformComponent : public Component
{
  public:

    TransformComponent();
    TransformComponent(int scale);
    TransformComponent(float x, float y, int width = 32, int height = 32, int scale = 1);

    void Init() override;
    void Update() override;

    Vector2D position;
    Vector2D velocity;

    int height;
    int width;
    int scale;

    int speed = 3;

};
