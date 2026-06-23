#pragma once

#include "Engine.h"

class Game {
public:
    explicit Game(Engine& engine);
    void run();

private:
    Engine& engine_;
};
