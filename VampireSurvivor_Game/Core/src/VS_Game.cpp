#include "VS_Game.h"
#include "GameScene.h"

VS_Game::VS_Game(GameEngine::Engine& engine)
    : m_engine(engine) {
}

void VS_Game::run() 
{
    GameEngine::SceneManagar::GetInstance().CreateScene("GameScene",std::make_unique<GameScene>());

    GameEngine::SceneManagar::GetInstance().LoadScene(0);

    m_engine.run();
}

