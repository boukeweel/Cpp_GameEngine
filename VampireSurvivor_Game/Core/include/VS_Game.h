#ifndef VS_GAME_H
#define VS_GAME_H

#include "Engine.h"

class VS_Game {
public:
    explicit VS_Game(GameEngine::Engine& engine);
    void run();

private:
    GameEngine::Engine& m_engine;
};

#endif