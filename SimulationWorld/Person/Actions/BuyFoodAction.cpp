//
// Created by boeken-work on 9/15/26.
//

#include "BuyFoodAction.h"

#include <iostream>
#include <ostream>

#include "Person.h"

namespace SimWorld
{
    BuyFoodAction::BuyFoodAction(Person* person)
    {
        m_Person = person;
        m_Effects[PersonKeys::HasFood] = true;
    }

    bool BuyFoodAction::Preform()
    {
        if (m_Person == nullptr)
            return false;

        m_Person->SetState(PersonKeys::HasFood, true);
        std::cout << "Got food" << std::endl;
        return true;
    }
} // SimWorld