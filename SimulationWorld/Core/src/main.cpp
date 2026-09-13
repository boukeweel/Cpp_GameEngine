#include "Engine.h"
#include "SimGame.h"

int main() {
    GameEngine::Engine engine("Simulation World", 1280, 720);
    if (!engine.init("Resources")) {
        return 1;
    }

    SimWorld::SimGame game{engine};
    game.run();

    return 0;
}
