#ifndef GAMESCENE_H
#define GAMESCENE_H

#include "IBaseScene.h"
#include "Scene.h"

namespace SurvivalGame
{
    class GameScene : public GameEngine::IBaseScene
    {
    public:
        void Load(GameEngine::Scene& scene) override;
        
        void LoadPlayer(GameEngine::Scene& scene);

        void LoadInput();
    };    
}


#endif