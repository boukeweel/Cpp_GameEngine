#include "MoveToPlayerComponent.h"
#include "Component.h"
#include "GameObject.h"
#include <glm/glm.hpp>
#include "Transform.h"
#include "EngineTime.h"

#include <iostream>

namespace SurvivalGame
{
    MoveToPlayerComponent::MoveToPlayerComponent(GameEngine::GameObject* parent, const GameEngine::GameObject* player, float speed)
    : GameEngine::Component(parent), m_pPlayer{player}, m_Speed{speed}
    {}

    void MoveToPlayerComponent::Update()
    {
        if(m_pPlayer != nullptr)
        {
            MoveToPlayer();
        }
    }

    void MoveToPlayerComponent::MoveToPlayer()
    {
        const glm::vec3 playerPosition{m_pPlayer->GetTransform().GetWorldPosition()};
        
        GameEngine::Transform& ownTransform{m_Owner->GetTransform()};

        const glm::vec3 ownPosition = ownTransform.GetWorldPosition();

        const glm::vec3 direction{playerPosition - ownPosition};

        glm::vec3 velocity = glm::normalize(direction) * m_Speed;

        glm::vec3 translation = velocity * GameEngine::EngineTime::GetdeltaTimeFloat();
        ownTransform.Translate(translation);
    }
}