//
// Created by boeken-work on 9/23/26.
//

#include "GOAPAgentComponent.h"

#include <assert.h>
#include <iostream>
#include <ostream>

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
        if (currentAction != nullptr)
        {
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
        if (!m_CurrentGoal->IsKeyRelated(key))
            ReCalculatedGoal();
    }

    GOAPAgentComponent::~GOAPAgentComponent() = default;

    void GOAPAgentComponent::ReCalculatedGoal()
    {
        Goal* newGoal = m_Planner->GetNewGoal(m_CurrentState,m_Goals);
        if (newGoal != nullptr && newGoal != m_CurrentGoal)
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
                m_CurrentState,
                m_CurrentGoal,
                m_AvailableActions
            );
        }
    }
} // SimWorld