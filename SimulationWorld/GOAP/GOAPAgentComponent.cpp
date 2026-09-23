//
// Created by boeken-work on 9/23/26.
//

#include "GOAPAgentComponent.h"

#include "Planner.h"

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
        m_AvailableActions.emplace_back(std::move(action));
    }

    void GOAPAgentComponent::AddGoal(std::unique_ptr<Goal> goal)
    {
        m_Goals.emplace_back(std::move(goal));
    }

    void GOAPAgentComponent::AddState(PersonKeys key, int value)
    {
        m_CurrentState[key] = value;
    }

    void GOAPAgentComponent::FixedUpdate()
    {
        if (m_CurrentGoal == nullptr || m_CurrentGoal->IsReached(m_CurrentState))
        {
            m_CurrentGoal = m_Planner->GetNewGoal(m_CurrentState,m_Goals);
            ReCalculatedPath();
        }

        if (m_CurrentPath.empty()) return;

        Action* currentAction = m_CurrentPath.front();
        if (currentAction != nullptr && currentAction->Preform())
        {
            m_CurrentPath.pop();
        }
    }

    void GOAPAgentComponent::SetState(PersonKeys key, int newValue)
    {
        const auto it = m_CurrentState.find(key);

        if (it != m_CurrentState.end() &&
            it->second == newValue)
        {
            return;
        }

        m_CurrentState[key] = newValue;
        ReCalculatedGoal(key);
    }

    GOAPAgentComponent::~GOAPAgentComponent() = default;

    void GOAPAgentComponent::ReCalculatedGoal(PersonKeys key)
    {
        if (m_CurrentGoal == nullptr || !m_CurrentGoal->IsKeyRelated(key))
        {
            Goal* newGoal = m_Planner->GetNewGoal(m_CurrentState,m_Goals);
            if (newGoal != nullptr && newGoal != m_CurrentGoal)
            {
                m_CurrentGoal = newGoal;
                ReCalculatedPath();
            }
        }
    }

    void GOAPAgentComponent::ReCalculatedPath()
    {
        if (m_CurrentGoal != nullptr)
        {
            m_CurrentPath = m_Planner->Plan(
                m_CurrentState,
                m_CurrentGoal,
                m_AvailableActions
            );
        }
    }
} // SimWorld