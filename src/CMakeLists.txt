add_library(My_library
  Game/Game.h
  Game/Game.cpp
  TextureManager/TextureManager.h
  TextureManager/TextureManager.cpp
  GameObject/GameObject.h
  GameObject/GameObject.cpp
  Map/Map.h
  Map/Map.cpp
  Vector2D/Vector2D.h
  Vector2D/Vector2D.cpp
  Collision/Collision.h
  Collision/Collision.cpp
  ECS/ECS.h
  ECS/ECS.cpp
  ECS/TransformComponent.h
  ECS/TransformComponent.cpp
  ECS/SpriteComponent.h
  ECS/SpriteComponent.cpp
  ECS/KeyboardController.h
  ECS/KeyboardController.cpp
  ECS/ColliderComponent.h
  ECS/ColliderComponent.cpp
  ECS/TileComponent.h
  ECS/TileComponent.cpp
  ECS/Components.h
  ECS/AnimationComponent.h
)

target_include_directories(My_library
  #PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src"
  PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
  PUBLIC ${SDL2_INCLUDE_DIRS}
  PUBLIC ${SDL2_IMAGE_INCLUDE_DIRS}
)
