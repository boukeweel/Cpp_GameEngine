//
// Created by boeken-work on 9/15/26.
//

#include "BuyFoodAction.h"

#include <iostream>
#include <ostream>

#include "GOAPAgentComponent.h"
#include "Person.h"

namespace SimWorld
{
    BuyFoodAction::BuyFoodAction(GOAPAgentComponent* agent)
    {
        m_GoapAgent = agent;
        m_Effects[PersonKeys::HasFood] = true;
    }

    bool BuyFoodAction::Preform()
    {
        if (m_GoapAgent == nullptr)
            return false;

        m_GoapAgent->SetState(PersonKeys::HasFood, true);
        std::cout << "Got food" << std::endl;
        return true;
    }
} // SimWorld