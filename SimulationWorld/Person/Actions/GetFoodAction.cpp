//
// Created by boeken-work on 9/15/26.
//

#include "GetFoodAction.h"

#include <iostream>
#include <ostream>

namespace SimWorld
{
    GetFoodAction::GetFoodAction(GameEngine::Event<PersonKeys,int>* changeStateEvent)
    {
        m_ChangeStateEvent = changeStateEvent;
        m_Effects[PersonKeys::HasFood] = true;
    }

    bool GetFoodAction::Preform()
    {
        if (m_ChangeStateEvent == nullptr)
            return false;

        m_ChangeStateEvent->Invoke(PersonKeys::HasFood, true);
        std::cout << "Got food" << std::endl;
        return true;
    }
} // SimWorld