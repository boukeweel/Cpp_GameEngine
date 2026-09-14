//
// Created by boeken-work on 9/14/26.
//

#include "EatAction.h"

#include <iostream>

namespace SimWorld
{
    EatAction::EatAction()
    {
        m_PreConditions[PersonKeys::HasFood] = true;
        m_Effects[PersonKeys::Hunger] = 0;
    }

    bool EatAction::Preform(PersonState &state)
    {
        //todo when inventory is done, it should remove a food item from the person inventory
        state[PersonKeys::Hunger] = 0;
        std::cout << "Eating" << std::endl;
        return true;
    }
} // SimWorld