#include "KeyboardController.h"

#include "Game/Game.h"
#include "TransformComponent.h"
#include "SpriteComponent.h"

#include <SDL2/SDL_keyboard.h>

void KeyboardController::Init()
{
    m_transform = &m_entity->GetComponent<TransformComponent>();
    m_sprite = &m_entity->GetComponent<SpriteComponent>();
}

void KeyboardController::Update()
{
    const Uint8* kb = SDL_GetKeyboardState(NULL);

    if (kb[SDL_SCANCODE_ESCAPE])
    {
        Game::isRunning = false;
    }

    Vector2D& vel = m_transform->velocity;
            vel.y = kb[SDL_SCANCODE_S] - kb[SDL_SCANCODE_W];
            vel.x = kb[SDL_SCANCODE_D] - kb[SDL_SCANCODE_A];

            if(vel.x !=0
                ||
                vel.y != 0)
            {
                m_sprite->PlayAnimation(WalkAnim);
                if(vel.x < 0)
                {
                    m_sprite->m_doSpriteFlip = SDL_FLIP_HORIZONTAL;
                }
                else
                {
                    m_sprite->m_doSpriteFlip = SDL_FLIP_NONE;
                }
            }
            else
            {
                m_sprite->PlayAnimation(IdleAnim);
            }
}
    
