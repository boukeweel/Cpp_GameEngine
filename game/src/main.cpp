#include "Engine.h"
#include "Game.h"

int main() {
    GameEngine::Engine engine("Small engine", 1280, 720);
    if (!engine.init()) {
        return 1;
    }

    Game game(engine);
    game.run();

    return 0;
}
