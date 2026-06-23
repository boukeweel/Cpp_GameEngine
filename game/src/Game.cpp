#include "Game.h"

Game::Game(GameEngine::Engine& engine)
    : engine_(engine) {
}

void Game::run() {
    engine_.run();
}
