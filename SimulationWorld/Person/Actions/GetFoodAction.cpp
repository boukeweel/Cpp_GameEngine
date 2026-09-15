//
// Created by boeken-work on 9/15/26.
//

#include "GetFoodAction.h"

#include <iostream>
#include <ostream>

namespace SimWorld
{
    GetFoodAction::GetFoodAction()
    {
        m_Effects[PersonKeys::HasFood] = true;
    }

    bool GetFoodAction::Preform(PersonState &state)
    {
        state[PersonKeys::HasFood] = true;
        std::cout << "Got food" << std::endl;
        return true;
    }
} // SimWorld