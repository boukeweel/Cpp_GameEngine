//
// Created by boeken-work on 9/15/26.
//

#include "HungerComponent.h"

#include <iostream>
#include <ostream>

#include "GameObject.h"
#include "Person.h"
#include "EatGoal.h"
#include "States.h"

namespace SimWorld
{
    HungerComponent::HungerComponent(GameEngine::GameObject *owner) : Component(owner)
    {
        auto PersonComp = m_Owner->GetComponent<Person>();
        m_CurrentState = PersonComp->GetCurrentState();
        m_EatGoal = PersonComp->GetGoal<EatGoal>();
    }

    void HungerComponent::FixedUpdate()
    {
        if (CurrentHungerTimer > HungerTimer)
        {
            std::cout << "Hunger Timer Reached" << std::endl;
            CurrentHungerTimer -= HungerTimer;
            UpdateHunger();
        }
    }

    void HungerComponent::AteFood()
    {
        m_EatGoal->ChangePriority(-1);
        m_Hunger = hunger::fed;
    }

    void HungerComponent::UpdateHunger()
    {
        switch (m_Hunger)
        {
            case hunger::fed:
                (*m_CurrentState)[PersonKeys::Hunger] = 1;
                m_EatGoal->ChangePriority(5);
                m_Hunger = hunger::Hungry;
                break;
            case hunger::Hungry:
                (*m_CurrentState)[PersonKeys::Hunger] = 2;
                m_EatGoal->ChangePriority(20);
                m_Hunger = hunger::starving;
                break;
            default:
                break;
        }
    }
} // SimWorld