//
// Created by boeken-work on 9/14/26.
//

#include "EatAction.h"
#include "HungerComponent.h"
#include <iostream>

#include "GOAPAgentComponent.h"
#include "Person.h"
#include "Inventory.h"

namespace SimWorld
{
    EatAction::EatAction(HungerComponent* hc,Person* agent) : m_Person{agent}, m_HungerComp{hc}
    {
        m_PreConditions[PersonKeys::HasFood] = true;
        m_Effects[PersonKeys::Hunger] = 0;
    }

    bool EatAction::Preform()
    {
        if (m_HungerComp == nullptr || m_Person == nullptr)
            return false;

        m_HungerComp->AteFood();

        m_Person->GetInventory().Remove(ItemType::Food,1);
        m_Person->GetGOAPAgentComponent()->SetState(PersonKeys::Hunger, 0);

        std::cout << "Eating" << std::endl;
        return true;
    }
} // SimWorld