//
// Created by boeken-work on 9/15/26.
//

#include "GetFoodAction.h"

#include <iostream>
#include <ostream>

#include "Person.h"

namespace SimWorld
{
    GetFoodAction::GetFoodAction(Person* person)
    {
        m_Person = person;
        m_Effects[PersonKeys::HasFood] = true;
    }

    bool GetFoodAction::Preform()
    {
        if (m_Person == nullptr)
            return false;

        m_Person->SetState(PersonKeys::HasFood, true);
        std::cout << "Got food" << std::endl;
        return true;
    }
} // SimWorld