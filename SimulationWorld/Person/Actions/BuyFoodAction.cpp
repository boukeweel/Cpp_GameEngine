//
// Created by boeken-work on 9/15/26.
//

#include "BuyFoodAction.h"

#include <iostream>
#include <ostream>

#include "GOAPAgentComponent.h"
#include "Person.h"
#include "WorldData.h"

namespace SimWorld
{
    BuyFoodAction::BuyFoodAction(Person* agent) : m_Person{agent}
    {
        m_Effects[PersonKeys::HasFood] = true;
    }

    bool BuyFoodAction::Preform()
    {
        if (m_Person == nullptr)
            return false;

        //todo I want the agent to hold there favorite food store, so I dont have to get it every time from the worldData
        auto store = WorldData::GetInstance().GetFoodStore();
        if (store == nullptr) return false;

        if (store->GetPrice() > m_Person->GetWallet().GetBalance())
            return false;

        store->Buy(m_Person->GetWallet(),m_Person->GetInventory(),1);

        std::cout << "Got food" << std::endl;
        return true;
    }
} // SimWorld