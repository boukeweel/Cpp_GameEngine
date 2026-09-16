//
// Created by boeken-work on 9/15/26.
//

#include "HungerComponent.h"

#include <iostream>
#include <ostream>

#include "GameObject.h"
#include "Person.h"
#include "EatGoal.h"
#include "EngineTime.h"
#include "States.h"

namespace SimWorld
{
    HungerComponent::HungerComponent(GameEngine::GameObject *owner) : Component(owner)
    {

    }

    void HungerComponent::Begin()
    {
        auto personComp = m_Owner->GetComponent<Person>();
        if (personComp != nullptr)
        {
            m_CurrentState = personComp->GetCurrentState();
            m_EatGoal = personComp->GetGoal<EatGoal>();
        }
    }

    void HungerComponent::FixedUpdate()
    {
        CurrentHungerTimer += GameEngine::EngineTime::GetFixedDeltaTime();
        if (CurrentHungerTimer >= HungerTimer)
        {
            std::cout << "Hunger Timer Reached" << std::endl;
            CurrentHungerTimer -= HungerTimer;
            UpdateHunger();
        }
    }

    void HungerComponent::AteFood()
    {
        m_EatGoal->ChangePriority(-1);
        m_Hunger = HungerLevel::fed;
    }

    void HungerComponent::UpdateHunger()
    {
        switch (m_Hunger)
        {
            case HungerLevel::fed:
                m_EatGoal->ChangePriority(5);
                m_Hunger = HungerLevel::Hungry;
                (*m_CurrentState)[PersonKeys::Hunger] = static_cast<int>(m_Hunger);
                break;
            case HungerLevel::Hungry:
                m_EatGoal->ChangePriority(20);
                m_Hunger = HungerLevel::starving;
                (*m_CurrentState)[PersonKeys::Hunger] = static_cast<int>(m_Hunger);
                break;
            default:
                break;
        }
    }
} // SimWorld