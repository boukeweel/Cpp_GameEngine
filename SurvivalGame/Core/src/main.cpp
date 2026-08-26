#include "Engine.h"
#include "SG_Game.h"

int main() {
    GameEngine::Engine engine("Survival game", 1280, 720);
    if (!engine.init("SurvivalGame/Resources")) {
        return 1;
    }
    SurvivalGame::SG_Game game(engine);
    game.run();
    return 0;
}


