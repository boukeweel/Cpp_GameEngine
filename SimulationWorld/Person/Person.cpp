//
// Created by boeken-work on 9/13/26.
//

#include "Person.h"

#include <iostream>
#include <ostream>

#include "../GOAP/Planner.h"
#include "Actions/EatAction.h"
#include "Goals/EatGoal.h"
#include "../GOAP/Action.h"
#include "GameObject.h"
#include "Actions/GetFoodAction.h"
#include "HungerComponent.h"
#include "Inventory.h"
#include "Wallet.h"

namespace SimWorld {
    Person::Person(GameEngine::GameObject *owner) : Component(owner)
    {
        m_Planner = std::make_unique<Planner>();
        m_Wallet = std::make_unique<Wallet>(*this,100);
        m_Inventory = std::make_unique<Inventory>();
    }

    void Person::Begin()
    {
        InitStates();
        InitActions();
        InitGoals();
    }

    void Person::SetState(PersonKeys key, int newValue)
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

    void Person::InitStates()
    {
        m_CurrentState[PersonKeys::HasFood] = false;
        m_CurrentState[PersonKeys::Hunger] = 0;
    }

    void Person::InitActions()
    {
        m_AvailableActions.emplace_back(
            std::make_unique<EatAction>
                (m_Owner->GetComponent<HungerComponent>(),this));
        m_AvailableActions.emplace_back(
            std::make_unique<GetFoodAction>(this));
    }

    void Person::InitGoals()
    {
        m_Goals.emplace_back(std::make_unique<EatGoal>());
    }

    void Person::ReCalculatedGoal(PersonKeys key)
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

    void Person::ReCalculatedPath()
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

    void Person::FixedUpdate()
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

    Person::~Person() = default;
} // SimWorld