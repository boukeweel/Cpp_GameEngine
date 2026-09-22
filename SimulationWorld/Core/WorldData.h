//
// Created by boeken-work on 9/22/26.
//

#ifndef GAMEENGINE_WORLDDATA_H
#define GAMEENGINE_WORLDDATA_H
#include <vector>

#include "FoodStore.h"
#include "Singleton.h"

namespace SimWorld
{
    class WorldData : public GameEngine::Singleton<WorldData>
    {
    public:
        //todo later should expand to be able to give back the closest store
        FoodStore* GetFoodStore();

        void AddFoodStore(FoodStore* foodStore);
    private:
        std::vector<FoodStore*> m_FoodStores;
    };
} // SimWorld

#endif //GAMEENGINE_WORLDDATA_H
