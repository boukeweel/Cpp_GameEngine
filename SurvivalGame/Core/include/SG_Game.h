#ifndef SG_GAME_H
#define SG_GAME_H

#include "Engine.h"

namespace SurvivalGame
{
    class SG_Game {
    public:
        explicit SG_Game(GameEngine::Engine& engine);
        void run();

    private:
        GameEngine::Engine& m_engine;
    };
}

#endif