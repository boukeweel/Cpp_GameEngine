//
// Created by boeken on 9/12/26.
//

#ifndef SIMWORLD_SIMULATIONSCENE_H
#define SIMWORLD_SIMULATIONSCENE_H
#include <memory>

#include "IBaseScene.h"

namespace GameEngine
{
    class GameObject;
}

namespace SimWorld {
    class SimulationScene : public GameEngine::IBaseScene {
    public:
        void Load(GameEngine::Scene& scene) override;

    private:
        std::unique_ptr<GameEngine::GameObject> CreatePerson();
    };
}



#endif //SIMWORLD_SIMULATIONSCENE_H
