//
// Created by boeken-work on 9/22/26.
//

#include "WorldData.h"

namespace SimWorld
{
    FoodStore * WorldData::GetFoodStore()
    {
        if (m_FoodStores.empty()) return nullptr;

        return m_FoodStores.front();
    }

    void WorldData::AddFoodStore(FoodStore* foodStore)
    {
        m_FoodStores.emplace_back(foodStore);
    }
} // SimWorld