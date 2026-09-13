//
// Created by boeken on 9/12/26.
//

#ifndef SimWorld_SIMULATIONSCENE_H
#define SimWorld_SIMULATIONSCENE_H
#include "IBaseScene.h"

namespace SimWorld {
    class SimulationScene : public GameEngine::IBaseScene {
    public:
        void Load(GameEngine::Scene& scene) override;
    };
}



#endif //GAMEENGINE_SIMULATIONSCENE_H
