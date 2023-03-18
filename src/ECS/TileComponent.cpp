
    #include "TileComponent.h"
    #include "TransformComponent.h"
    #include "SpriteComponent.h"
    
    TileComponent::TileComponent(int x, int y, int w, int h, TileSet* tSet, int id)
    {
      m_tileRect.x = x;
      m_tileRect.y = y;
      m_tileRect.w = w;
      m_tileRect.h = h;

      m_tileSet = tSet;
      m_tileID = id;
    }

    void TileComponent::Init()
    {
      if(!m_entity->HasComponent<TransformComponent>()){
        m_entity->AddComponent<TransformComponent>(
                static_cast<float>(TILESET_SCALE*m_tileRect.x),
                static_cast<float>(TILESET_SCALE*m_tileRect.y), 
                m_tileRect.w, 
                m_tileRect.h, TILESET_SCALE);
      }
      m_transform = &m_entity->GetComponent<TransformComponent>();

      m_entity->AddComponent<SpriteComponent>(m_tileSet, m_tileID);
      m_sprite = &m_entity->GetComponent<SpriteComponent>();
    }