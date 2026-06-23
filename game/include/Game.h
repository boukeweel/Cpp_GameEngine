#pragma once

#include "Engine.h"

class Game {
public:
    explicit Game(GameEngine::Engine& engine);
    void run();

private:
    GameEngine::Engine& engine_;
};
