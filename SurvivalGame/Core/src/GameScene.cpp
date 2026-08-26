#include "GameScene.h"
#include "InputData.h"
#include "InputHandler.h"
#include "Scene.h"
#include "GameObject.h"
#include "SGMoveCommand.h"
#include "SGPlayerMovement.h"
#include "Transform.h"
#include "SpriteRenderer.h"
#include "SGGameData.h"
#include "MoveToPlayerComponent.h"
#include "RectColliderComponent.h"

namespace SurvivalGame
{

    void GameScene::Load(GameEngine::Scene& scene)
    {

        LoadInput();


        scene.AddObject(LoadPlayer());

        auto Enemy = LoadEnemy();
        Enemy->GetTransform().SetPosition(300.f,300.f,0);
        scene.AddObject(std::move(Enemy));
        Enemy = LoadEnemy();
        Enemy->GetTransform().SetPosition(300.f,200.f,0);
        scene.AddObject(std::move(Enemy));
        Enemy = LoadEnemy();
        Enemy->GetTransform().SetPosition(10.f,500.f,0);
        scene.AddObject(std::move(Enemy));
        Enemy = LoadEnemy();
        Enemy->GetTransform().SetPosition(200.f,450.f,0);
        scene.AddObject(std::move(Enemy));
        Enemy = LoadEnemy();
        Enemy->GetTransform().SetPosition(50.f,420.f,0);
        scene.AddObject(std::move(Enemy));
        Enemy = LoadEnemy();
        Enemy->GetTransform().SetPosition(150.f,350.f,0);
        scene.AddObject(std::move(Enemy));
    }

    void GameScene::LoadInput()
    {
        auto& input = GameEngine::InputHandler::GetInstance();

	    input.AddInput(GameEngine::InputKeys::ARROW_UP, GameEngine::InputAction{{SDL_SCANCODE_UP}});
	    input.AddInput(GameEngine::InputKeys::ARROW_DOWN, GameEngine::InputAction{{SDL_SCANCODE_DOWN}});
	    input.AddInput(GameEngine::InputKeys::ARROW_LEFT, GameEngine::InputAction{{SDL_SCANCODE_LEFT}});
	    input.AddInput(GameEngine::InputKeys::ARROW_RIGHT, GameEngine::InputAction{{SDL_SCANCODE_RIGHT}});
    }

    std::unique_ptr<GameEngine::GameObject> GameScene::LoadPlayer()
    {
        auto& input = GameEngine::InputHandler::GetInstance();

        auto player = std::make_unique<GameEngine::GameObject>();
        player->AddComponent<GameEngine::SpriteRenderer>("/Images/AllyTemp.png");
        auto moveObject = player->AddComponent<SGPlayerMovement>(75);
        player->GetTransform().SetPosition(100.f,100.f,0);
        player->GetTransform().SetScale(2.f,2.f);
        
        input.AddCommand(GameEngine::InputKeys::ARROW_LEFT, GameEngine::InputStates::Held
            , std::make_unique<SGMoveCommand>(moveObject, glm::vec3{-1.f, 0.f, 0.f}));
        input.AddCommand(GameEngine::InputKeys::ARROW_RIGHT, GameEngine::InputStates::Held
            , std::make_unique<SGMoveCommand>(moveObject, glm::vec3{1.f, 0.f, 0.f}));
        input.AddCommand(GameEngine::InputKeys::ARROW_UP, GameEngine::InputStates::Held
            , std::make_unique<SGMoveCommand>(moveObject, glm::vec3{0.f, 1.f, 0.f}));
        input.AddCommand(GameEngine::InputKeys::ARROW_DOWN, GameEngine::InputStates::Held
            , std::make_unique<SGMoveCommand>(moveObject, glm::vec3{0.f, -1.f, 0.f}));
        
        SGGameDate::GetInstance().SetPlayer(player.get());
    
        rawPlayerPtr = player.get();
        return std::move(player);
    }

    std::unique_ptr<GameEngine::GameObject> GameScene::LoadEnemy()
    {
        auto enemy = std::make_unique<GameEngine::GameObject>();
        enemy->AddComponent<GameEngine::SpriteRenderer>("/Images/EnemyTemp.png");
        enemy->GetTransform().SetPosition(300.f,300.f,0);
        enemy->GetTransform().SetScale(1.5f,1.5f);

        enemy->AddComponent<GameEngine::RectColliderComponent>();

        /*float enemySpeed = 20.f;
        enemy->AddComponent<MoveToPlayerComponent>(rawPlayerPtr, enemySpeed);*/

        return std::move(enemy);
    }
}
