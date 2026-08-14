#include "Game.h"
#include "InputData.h"
#include "InputHandler.h"
#include <memory>
#include <utility>
#include "TestScene.h"

Game::Game(GameEngine::Engine& engine)
    : m_engine(engine) {
}

void Game::run() 
{
    GameEngine::SceneManagar::GetInstance().CreateScene("Test_Scene",std::make_unique<TestScene>());

    m_engine.run();
}

