#include "SpriteComponent.h"
#include "TransformComponent.h"

    SpriteComponent::SpriteComponent(const char* path, bool isAnimated)
    {
      m_isAnimated = isAnimated;

      Animation idle = Animation(0, 4, 250);
      Animation walk = Animation(1, 4, 100);

    
      m_animations.emplace_back(idle);
      m_animations.emplace_back(walk);

      SetTex(path);
    }

    SpriteComponent::SpriteComponent(TileSet* tSet, int id)
    {
      m_tileSet = tSet;
      m_tileID = id;

      SetTex(tSet->path);
    }

    void SpriteComponent::Init()
    {
      if(m_isAnimated)
      {
        PlayAnimation(IdleAnim);
      }

      m_transform = &m_entity->GetComponent<TransformComponent>();

      if(m_tileID != -1)
      {
        m_srcRect.x = (m_tileID % TILESET_WIDTH) * 16;
        m_srcRect.y = (static_cast<int>(floor(m_tileID / TILESET_WIDTH))) * 16;
        m_srcRect.w = m_srcRect.h = 16;
      }
      else
      {
        m_srcRect.x = m_srcRect.y = 0;
        m_srcRect.w = m_transform->width;
        m_srcRect.h = m_transform->height;
      }
    }

    void SpriteComponent::Update()
    {
      if(m_isAnimated)
      {
        int animNum = static_cast<int>(SDL_GetTicks() / m_animSpeed) % m_animFrames;
        m_srcRect.x = m_srcRect.w * animNum;
        m_srcRect.y = m_animIndex * m_transform->height;
      }

      m_destRect.x = static_cast<int>(m_transform->position.x);
      m_destRect.y = static_cast<int>(m_transform->position.y);
      m_destRect.w = m_transform->width * m_transform->scale;
      m_destRect.h = m_transform->height * m_transform->scale;
    }

    void SpriteComponent::PlayAnimation(anims animName)
    {
      m_animFrames = m_animations[animName].m_frames;
      m_animIndex = m_animations[animName].m_index;
      m_animSpeed = m_animations[animName].m_speed;
    }