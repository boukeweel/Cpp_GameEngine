#include "Engine.h"
#include "Game.h"

int main() {
    GameEngine::Engine engine("Small engine", 720, 480);
    if (!engine.init("Resources")) {
        return 1;
    }

    Game game(engine);
    game.run();

    return 0;
}
