//
// Created by boeken-work on 9/22/26.
//

#ifndef GAMEENGINE_WORLDDATA_H
#define GAMEENGINE_WORLDDATA_H
#include <vector>

#include "FoodStore.h"
#include "Singleton.h"
#include "WorldState.h"

namespace SimWorld
{
    class WorldData : public GameEngine::Singleton<WorldData>
    {
    public:
        //todo later should expand to be able to give back the closest store
        FoodStore* GetFoodStore();

        void AddFoodStore(FoodStore* foodStore);
        WorldState& GetWorldState() { return m_WorldState; }
        const WorldState& GetWorldState() const { return m_WorldState; }
    private:
        std::vector<FoodStore*> m_FoodStores;
        WorldState m_WorldState;
    };
} // SimWorld

#endif //GAMEENGINE_WORLDDATA_H
