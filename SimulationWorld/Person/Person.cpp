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
        InitStates();
        InitActions();
        InitGoals();

        m_CurrentGoal = m_Goals[0];
        m_CurrentPath = m_Planner->Plan(m_CurrentState,m_CurrentGoal,m_AvailableActions);
    }

    void Person::InitStates()
    {
        m_CurrentState[PersonKeys::HasFood] = false;
        m_CurrentState[PersonKeys::Hunger] = 1;
    }

    void Person::InitActions()
    {
        m_AvailableActions.emplace_back(new EatAction(m_Owner->GetComponent<HungerComponent>()));
        m_AvailableActions.emplace_back(new GetFoodAction());
    }

    void Person::InitGoals()
    {
        m_Goals.emplace_back(new EatGoal());
    }

    void Person::FixedUpdate()
    {
        if (m_CurrentPath.empty())
            return;

        Action* currentAction = m_CurrentPath.front();
        if (currentAction != nullptr && currentAction->Preform(m_CurrentState))
        {
            m_CurrentPath.pop();
        }
    }

    Person::~Person()
    {
        for (auto action : m_AvailableActions)
        {
            delete action;
            action = nullptr;
        }
        for (auto goal : m_Goals)
        {
            delete goal;
            goal = nullptr;
        }
    }
} // SimWorld