//
// Created by boeken-work on 9/13/26.
//

#include "Person.h"
#include "Planner.h"
#include "Goals/EatGoal.h"

namespace SimWorld {
    Person::Person(GameEngine::GameObject *owner) : Component(owner)
    {
        m_Planner = std::make_unique<Planner>();
        InitStates();
        InitActions();
        InitGoals();
    }

    void Person::InitStates()
    {
        m_CurrentState[PersonKeys::HasFood] = false;
        m_CurrentState[PersonKeys::Hunger] = 0;
    }

    void Person::InitActions()
    {
        
    }

    void Person::InitGoals()
    {
        m_Goals.emplace_back(new EatGoal());
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