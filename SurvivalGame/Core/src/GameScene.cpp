#include "GameScene.h"
#include "InputData.h"
#include "InputHandler.h"
#include "Scene.h"
#include "GameObject.h"
#include "SGMoveCommand.h"
#include "SGPlayerMovement.h"
#include "Transform.h"
#include "SpriteRenderer.h"

namespace SurvivalGame
{

    void GameScene::Load(GameEngine::Scene& scene)
    {
        LoadInput();
        LoadPlayer(scene);
    }

    void GameScene::LoadInput()
    {
        auto& input = GameEngine::InputHandler::GetInstance();

	    input.AddInput(GameEngine::InputKeys::ARROW_UP, GameEngine::InputAction{{SDL_SCANCODE_UP}});
	    input.AddInput(GameEngine::InputKeys::ARROW_DOWN, GameEngine::InputAction{{SDL_SCANCODE_DOWN}});
	    input.AddInput(GameEngine::InputKeys::ARROW_LEFT, GameEngine::InputAction{{SDL_SCANCODE_LEFT}});
	    input.AddInput(GameEngine::InputKeys::ARROW_RIGHT, GameEngine::InputAction{{SDL_SCANCODE_RIGHT}});
    }

    void GameScene::LoadPlayer(GameEngine::Scene& scene)
    {
        auto& input = GameEngine::InputHandler::GetInstance();

        auto player = std::make_unique<GameEngine::GameObject>();
        player->AddComponent<GameEngine::SpriteRenderer>("/Images/AllyTemp.png");
        auto moveObject = player->AddComponent<SGPlayerMovement>(75);
        player->GetTransform().SetPosition(50.f,100.f,0);
        player->GetTransform().SetScale(2.f,2.f);
        
        input.AddCommand(GameEngine::InputKeys::ARROW_LEFT, GameEngine::InputStates::Held
            , std::make_unique<SGMoveCommand>(moveObject, glm::vec3{-1.f, 0.f, 0.f}));
        input.AddCommand(GameEngine::InputKeys::ARROW_RIGHT, GameEngine::InputStates::Held
            , std::make_unique<SGMoveCommand>(moveObject, glm::vec3{1.f, 0.f, 0.f}));
        input.AddCommand(GameEngine::InputKeys::ARROW_UP, GameEngine::InputStates::Held
            , std::make_unique<SGMoveCommand>(moveObject, glm::vec3{0.f, 1.f, 0.f}));
        input.AddCommand(GameEngine::InputKeys::ARROW_DOWN, GameEngine::InputStates::Held
            , std::make_unique<SGMoveCommand>(moveObject, glm::vec3{0.f, -1.f, 0.f}));
        
        scene.AddObject(std::move(player));
    }
}