#include "Game.h"

Game::Game(Engine& engine)
    : engine_(engine) {
}

void Game::run() {
    engine_.run();
}
