#include "SG_Game.h"
#include "GameScene.h"

namespace SurvivalGame
{
    SG_Game::SG_Game(GameEngine::Engine& engine)
        : m_engine(engine) {
    }
    
    void SG_Game::run() 
    {
        GameEngine::SceneManagar::GetInstance().CreateScene("GameScene",std::make_unique<GameScene>());
    
        GameEngine::SceneManagar::GetInstance().LoadScene(0);
    
        m_engine.run();
    }

}


