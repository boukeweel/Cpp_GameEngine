//
// Created by boeken-work on 9/13/26.
//

#include "Person.h"

#include <iostream>
#include <ostream>

#include "Planner.h"
#include "Actions/EatAction.h"
#include "Goals/EatGoal.h"
#include "Action.h"
#include "GameObject.h"
#include "Actions/GetFoodAction.h"
#include "HungerComponent.h"

namespace SimWorld {
    Person::Person(GameEngine::GameObject *owner) : Component(owner)
    {
        m_Planner = std::make_unique<Planner>();
        m_ChangeStateEvent.Subscribe([this](PersonKeys key, int value)
        {
            SetState(key, value);
        }
);
    }

    void Person::Begin()
    {
        InitStates();
        InitActions();
        InitGoals();

        m_CurrentGoal = m_Goals[0].get();
        m_CurrentPath = m_Planner->Plan(m_CurrentState,m_CurrentGoal,m_AvailableActions);
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
                (m_Owner->GetComponent<HungerComponent>(),&m_ChangeStateEvent));
        m_AvailableActions.emplace_back(
            std::make_unique<GetFoodAction>(&m_ChangeStateEvent));
    }

    void Person::InitGoals()
    {
        m_Goals.emplace_back(std::make_unique<EatGoal>());
    }

    void Person::FixedUpdate()
    {
        if (m_CurrentPath.empty())
            return;

        Action* currentAction = m_CurrentPath.front();
        if (currentAction != nullptr && currentAction->Preform())
        {
            m_CurrentPath.pop();
        }
    }

    Person::~Person() = default;
} // SimWorld