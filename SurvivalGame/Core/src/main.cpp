#include "Engine.h"
#include "SG_Game.h"

int main() {
    GameEngine::Engine engine("Vampire Survivor", 720, 480);
    if (!engine.init("Resources")) {
        return 1;
    }
    SurvivalGame::SG_Game game(engine);
    game.run();
    return 0;
}


