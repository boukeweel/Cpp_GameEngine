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
#include "GOAPAgentComponent.h"
#include "../../GOAP/States.h"

namespace SimWorld
{
    HungerComponent::HungerComponent(GameEngine::GameObject *owner) : Component(owner)
    {

    }

    void HungerComponent::Begin()
    {
        m_GoapAgent = m_Owner->GetComponent<Person>()->GetGOAPAgentComponent();
        if (m_GoapAgent != nullptr)
        {
            m_EatGoal = m_GoapAgent->GetGoal<EatGoal>();
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
                break;
            case HungerLevel::Hungry:
                m_EatGoal->ChangePriority(20);
                m_Hunger = HungerLevel::starving;
                break;
            default:
                break;
        }
        m_GoapAgent->SetState(
                    PersonKeys::Hunger, static_cast<int>(m_Hunger));
    }
} // SimWorld