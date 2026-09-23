//
// Created by boeken on 9/21/26.
//

#include "FoodStore.h"

#include <cassert>
#include <iostream>
#include <ostream>

#include "WorldData.h"

namespace SimWorld
{
    FoodStore::FoodStore(GameEngine::GameObject* owner,int pricePerFood) : Component(owner),
        m_pricePerFood(pricePerFood)
    {
        WorldData::GetInstance().AddFoodStore(this);
    }

    bool FoodStore::Buy(Wallet& buyerWallet, Inventory& buyerInventory, int amount)
    {
       if (amount <= 0) return false;

        int totalCost = amount * m_pricePerFood;

        if (!buyerWallet.Withdraw(totalCost))
        {
            return false;
        }

        buyerInventory.Add(ItemType::Food, amount);
        std::cout << "Bought food" << std::endl;
        return true;
    }

    int FoodStore::GetPrice() const
    {
        return m_pricePerFood;
    }
} // SimWorld