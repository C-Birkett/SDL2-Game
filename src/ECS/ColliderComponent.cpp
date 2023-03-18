#include "ColliderComponent.h"
#include "TransformComponent.h"

ColliderComponent::ColliderComponent(std::string tag)
:m_tag(tag)
{

}

void ColliderComponent::Init()
{
      //ColliderComponent reqires TransformComponent
      if(!m_entity->HasComponent<TransformComponent>())
      {
        m_entity->AddComponent<TransformComponent>();
      }
      m_transform = &m_entity->GetComponent<TransformComponent>();

      //Game::colliders.push_back(this);
}

void ColliderComponent::Update()
{
      m_collider.x = static_cast<int>(m_transform->position.x);
      m_collider.y = static_cast<int>(m_transform->position.y);
      m_collider.w = m_transform->width * m_transform->scale;
      m_collider.h = m_transform->height * m_transform->scale;
}
