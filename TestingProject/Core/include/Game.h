#ifndef GAME_H
#define GAME_H

#include "Engine.h"

class Game {
public:
    explicit Game(GameEngine::Engine& engine);
    void run();

private:
    GameEngine::Engine& m_engine;
};

#endif //GAME_H