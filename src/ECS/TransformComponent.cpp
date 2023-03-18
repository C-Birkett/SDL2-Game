
    #include "TransformComponent.h"

    TransformComponent::TransformComponent()
    {
      position.Zero();
    }

    TransformComponent::TransformComponent(int scle)
    {
        position.Zero();
        scale = scle;
    }

    TransformComponent::TransformComponent(float x, float y, int wdth /*= 32*/, int hght/*= 32*/, int scle/*= 1*/)
    {
      position.x = x;
      position.y = y;
      width = wdth;
      height = hght;
      scale = scle;
    }

    void TransformComponent::Init()
    {
      velocity.Zero();
    }
    
    void TransformComponent::Update()
    {
      position.x += velocity.x * speed;
      position.y += velocity.y * speed;
    }