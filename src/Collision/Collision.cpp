#include "Collision.h"
#include "ECS/ColliderComponent.h"

bool Collision::AABB(const SDL_Rect &recA, const SDL_Rect &recB)
{
  if(
        recA.x + recA.w >= recB.x &&
        recB.x + recB.w >= recA.x &&
        recA.y + recA.h >= recB.y &&
        recB.y + recB.h >= recA.y
    )
  {
    return true;
  }

  else
  {
  return false;
  }
}

bool Collision::AABB(const ColliderComponent& colA, const ColliderComponent& colB)
{
  if(AABB(colA.GetCollider(), colB.GetCollider()))
  {
    std::cout << colA.GetTag() << " hit: " << colB.GetTag() << std::endl;
    return true;
  }
  else
  {
    return false;
  }
}
