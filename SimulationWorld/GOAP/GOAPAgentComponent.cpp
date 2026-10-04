//
// Created by boeken-work on 9/23/26.
//

#include "GOAPAgentComponent.h"

#include <assert.h>
#include <iostream>
#include <ostream>

#include <glm/glm.hpp>

#include "Action.h"
#include "EngineTime.h"
#include "GameObject.h"
#include "Planner.h"
#include "Transform.h"
#include "WorldData.h"

namespace SimWorld
{
    GOAPAgentComponent::GOAPAgentComponent(GameEngine::GameObject *owner) : Component(owner)
    {
        m_Planner = std::make_unique<Planner>();
    }

    void GOAPAgentComponent::Begin()
    {

    }

    void GOAPAgentComponent::AddAction(std::unique_ptr<Action> action)
    {
        if (action == nullptr)
            return;

        action->SetAgentOwner(m_Owner);
        m_AvailableActions.emplace_back(std::move(action));
    }

    void GOAPAgentComponent::AddGoal(std::unique_ptr<Goal> goal)
    {
        m_Goals.emplace_back(std::move(goal));
    }

    void GOAPAgentComponent::AddState(PersonalKey key, int value)
    {
        m_PersonalState.Set(key, value);
    }

    bool GOAPAgentComponent::TryMoveToCurrentActionTarget()
    {
        if (m_CurrentPath.empty())
            return false;

        Action* currentAction = m_CurrentPath.front();
        if (currentAction == nullptr || !currentAction->HasTarget() || currentAction->IsInRange() || m_Owner == nullptr)
            return false;

        const glm::vec3 targetPosition = currentAction->GetTargetPosition();
        glm::vec3 ownPosition = m_Owner->GetTransform().GetWorldPosition();
        glm::vec3 direction = targetPosition - ownPosition;

        const float distance = glm::length(direction);
        if (distance <= 0.0001f)
            return false;

        direction = glm::normalize(direction);
        const glm::vec3 movement = direction * m_MoveSpeed * GameEngine::EngineTime::GetdeltaTimeFloat();
        m_Owner->GetTransform().Translate(movement);
        return true;
    }

    void GOAPAgentComponent::FixedUpdate()
    {
        const WorldState& worldState = WorldData::GetInstance().GetWorldState();
        if (m_CurrentGoal == nullptr || m_CurrentGoal->IsReached(m_PersonalState, worldState))
        {
            m_CurrentGoal = m_Planner->GetNewGoal(m_PersonalState, worldState, m_Goals);
            ReCalculatedPath();
        }

        if (m_CurrentPath.empty()) return;

        Action* currentAction = m_CurrentPath.front();
        if (currentAction == nullptr)
            return;

        if (currentAction->HasTarget() && !currentAction->IsInRange())
        {
            if (TryMoveToCurrentActionTarget())
                return;
        }

        switch (currentAction->Preform())
        {
            case ActionState::Completed:
                m_CurrentPath.pop();
                break;
            case ActionState::Running:
                break;
            case ActionState::Aborted:
                //The action got aborted so something big went wrong
                std::cout << "The action " << currentAction->GetName()
                           << " aborted, something went really wrong" << std::endl;
                assert(false && "Action aborted, something went really wrong");
                break;
            case ActionState::Failed:
                //Aborted or failed means its atm unable to completed this action
                ReCalculatedGoal();
                break;
        }
    }

    void GOAPAgentComponent::SetState(PersonalKey key, int newValue)
    {
        if (m_PersonalState.Has(key) && m_PersonalState.Get(key) == newValue)
        {
            return;
        }

        m_PersonalState.Set(key, newValue);
        if (m_CurrentGoal == nullptr || !m_CurrentGoal->IsPersonalKeyRelated(key))
            ReCalculatedGoal();
    }

    GOAPAgentComponent::~GOAPAgentComponent() = default;

    void GOAPAgentComponent::ReCalculatedGoal()
    {
        const WorldState& worldState = WorldData::GetInstance().GetWorldState();
        Goal* newGoal = m_Planner->GetNewGoal(m_PersonalState, worldState, m_Goals);
        if (newGoal != m_CurrentGoal)
        {
            m_CurrentGoal = newGoal;
            ReCalculatedPath();
        }
    }

    void GOAPAgentComponent::ReCalculatedPath()
    {
        if (m_CurrentGoal != nullptr)
        {
            m_CurrentPath = m_Planner->Plan(
                m_PersonalState,
                WorldData::GetInstance().GetWorldState(),
                m_CurrentGoal,
                m_AvailableActions
            );
        }
    }
} // SimWorld