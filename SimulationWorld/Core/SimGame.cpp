//
// Created by boeken on 9/12/26.
//
#include "SimGame.h"
#include "InputHandler.h"
#include <memory>
#include "Scenes/SimulationScene.h"

namespace SimWorld {

    SimGame::SimGame(GameEngine::Engine& engine)
        : m_engine(engine) {
    }

    void SimGame::run()
    {
        GameEngine::SceneManagar::GetInstance().CreateScene("Test_Scene",std::make_unique<SimulationScene>());
        GameEngine::SceneManagar::GetInstance().LoadScene(0);

        m_engine.run();
    }
}

