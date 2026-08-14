#include "SGPlayerMovement.h"
#include "Component.h"
#include <glm/geometric.hpp>
#include "Transform.h"
#include <glm/vec3.hpp>
#include "EngineTime.h"

namespace SurvivalGame
{
    SGPlayerMovement::SGPlayerMovement(GameEngine::GameObject* parent, float speed) : GameEngine::Component(parent), m_speed(speed){}

    void SGPlayerMovement::Move(glm::vec3 direction)
    {
        glm::vec3 velocity = glm::normalize(direction) * m_speed;

    	m_Owner->GetTransform().Translate(velocity * GameEngine::EngineTime::GetdeltaTimeFloat());
    }   
}

