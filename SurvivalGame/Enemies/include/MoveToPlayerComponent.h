#ifndef MOVE_TO_PLAYER_COMPONENT_h
#define MOVE_TO_PLAYER_COMPONENT_h

#include "Component.h"
#include <glm/vec3.hpp>

namespace SurvivalGame
{

    class MoveToPlayerComponent : public GameEngine::Component
    {
    public:
        MoveToPlayerComponent(GameEngine::GameObject* parent, const GameEngine::GameObject* player, float speed = 50);

        void Update() override;

    private:
        void MoveToPlayer();

        const GameEngine::GameObject* m_pPlayer{nullptr};

        float m_Speed{50.f};
    };
}

#endif