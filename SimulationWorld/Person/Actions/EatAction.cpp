//
// Created by boeken-work on 9/14/26.
//

#include "EatAction.h"
#include "HungerComponent.h"
#include <iostream>

namespace SimWorld
{
    EatAction::EatAction(HungerComponent* hc)
    {
        m_PreConditions[PersonKeys::HasFood] = true;
        m_Effects[PersonKeys::Hunger] = 0;
        m_HungerComp = hc;
    }

    bool EatAction::Preform(PersonState &state)
    {
        //todo when inventory is done, it should remove a food item from the person inventory
        m_HungerComp->AteFood();
        state[PersonKeys::Hunger] = 0;
        std::cout << "Eating" << std::endl;
        return true;
    }
} // SimWorld