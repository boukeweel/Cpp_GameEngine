//
// Created by boeken-work on 9/14/26.
//

#include "EatAction.h"
#include "HungerComponent.h"
#include <iostream>

#include "GOAPAgentComponent.h"
#include "Person.h"

namespace SimWorld
{
    EatAction::EatAction(HungerComponent* hc,GOAPAgentComponent* agent)
    {
        m_GoapAgent = agent;
        m_PreConditions[PersonKeys::HasFood] = true;
        m_Effects[PersonKeys::Hunger] = 0;
        m_HungerComp = hc;

    }

    bool EatAction::Preform()
    {
        if (m_HungerComp == nullptr || m_GoapAgent == nullptr)
            return false;

        m_HungerComp->AteFood();

        m_GoapAgent->SetState(PersonKeys::HasFood, false);
        m_GoapAgent->SetState(PersonKeys::Hunger, 0);

        std::cout << "Eating" << std::endl;
        return true;
    }
} // SimWorld