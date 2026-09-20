//
// Created by boeken-work on 9/14/26.
//

#include "EatAction.h"
#include "HungerComponent.h"
#include <iostream>

#include "Person.h"

namespace SimWorld
{
    EatAction::EatAction(HungerComponent* hc,Person* person)
    {
        m_Person = person;
        m_PreConditions[PersonKeys::HasFood] = true;
        m_Effects[PersonKeys::Hunger] = 0;
        m_HungerComp = hc;

    }

    bool EatAction::Preform()
    {
        if (m_HungerComp == nullptr || m_Person == nullptr)
            return false;

        m_HungerComp->AteFood();

        m_Person->SetState(PersonKeys::HasFood, false);
        m_Person->SetState(PersonKeys::Hunger, 0);

        std::cout << "Eating" << std::endl;
        return true;
    }
} // SimWorld