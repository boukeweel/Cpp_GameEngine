#include "TestScene.h"
#include "Scene.h"
#include "Game.h"
#include "Canvas.h"
#include "CanvasObject.h"
#include "GameObject.h"
#include "InputData.h"
#include "InputHandler.h"
#include "MoveCommand.h"
#include "PlayerMovement.h"
#include "ResourceManger.h"
#include "SpriteRenderer.h"
#include <memory>
#include <utility>

#include "RandomFunctions.h"
#include "RectColliderComponent.h"
#include "TextComponent.h"
#include "Transform.h" 
#include "UITextElement.h"
#include "UITransform.h"

void TestScene::Load(GameEngine::Scene& scene)
{


    /*float enemySpeed = 20.f;
    enemy->AddComponent<MoveToPlayerComponent>(rawPlayerPtr, enemySpeed);*/

    for (int i = 0; i < 100; ++i) {
        auto Cube = std::make_unique<GameEngine::GameObject>();
        Cube->AddComponent<GameEngine::SpriteRenderer>("/images/Dection_Cube.png");
        Cube->GetTransform().SetScale(1.f,1.f);
        Cube->AddComponent<GameEngine::RectColliderComponent>();
        Cube->GetTransform().SetPosition(GameEngine::Random::RandomF(0,1280.f),GameEngine::Random::RandomF(0,720.f),0);
        scene.AddObject(std::move(Cube));
    }
}