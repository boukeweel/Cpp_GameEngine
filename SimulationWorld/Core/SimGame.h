#ifndef SIM_GAME_H
#define SIM_GAME_H

#include "Engine.h"

namespace SimWorld {
    class SimGame {
    public:
        explicit SimGame(GameEngine::Engine& engine);
        void run();

    private:
        GameEngine::Engine& m_engine;
    };
}

#endif //SIM_GAME_H