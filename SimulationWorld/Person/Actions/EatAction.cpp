//
// Created by boeken-work on 9/14/26.
//

#include "EatAction.h"
#include "HungerComponent.h"
#include <iostream>

namespace SimWorld
{
    EatAction::EatAction(HungerComponent* hc, GameEngine::Event<PersonKeys,int>* changeStateEvent)
    {
        m_ChangeStateEvent = changeStateEvent;
        m_PreConditions[PersonKeys::HasFood] = true;
        m_Effects[PersonKeys::Hunger] = 0;
        m_HungerComp = hc;

    }

    bool EatAction::Preform()
    {
        if (m_HungerComp == nullptr || m_ChangeStateEvent == nullptr)
            return false;

        m_HungerComp->AteFood();

        m_ChangeStateEvent->Invoke(PersonKeys::HasFood, false);
        m_ChangeStateEvent->Invoke(PersonKeys::Hunger, 0);

        std::cout << "Eating" << std::endl;
        return true;
    }
} // SimWorld