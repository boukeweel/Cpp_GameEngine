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
    private:
        void LoadInput();
        std::unique_ptr<GameEngine::GameObject> LoadPlayer();
        std::unique_ptr<GameEngine::GameObject> LoadEnemy();

        GameEngine::GameObject* rawPlayerPtr{nullptr};
    };    
}


#endif