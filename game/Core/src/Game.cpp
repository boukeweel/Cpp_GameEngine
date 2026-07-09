#include "Game.h"
#include "Canvas.h"
#include "CanvasObject.h"
#include "GameObject.h"
#include "InputData.h"
#include "InputHandler.h"
#include "MoveCommand.h"
#include "PlayerMovement.h"
#include "ResourceManger.h"
#include "Scene.h"
#include "SpriteRenderer.h"
#include <memory>
#include <utility>
#include "TextComponent.h"
#include "Transform.h" 
#include "UITextElement.h"
#include "UITransform.h"

Game::Game(GameEngine::Engine& engine)
    : m_engine(engine) {
}

void Game::run() 
{
    auto& input = GameEngine::InputHandler::GetInstance();

	input.AddInput(GameEngine::InputKeys::ARROW_UP, GameEngine::InputAction{{SDL_SCANCODE_UP}});
	input.AddInput(GameEngine::InputKeys::ARROW_DOWN, GameEngine::InputAction{{SDL_SCANCODE_DOWN}});
	input.AddInput(GameEngine::InputKeys::ARROW_LEFT, GameEngine::InputAction{{SDL_SCANCODE_LEFT}});
	input.AddInput(GameEngine::InputKeys::ARROW_RIGHT, GameEngine::InputAction{{SDL_SCANCODE_RIGHT}});

    auto scene = std::make_unique<GameEngine::Scene>("Main Scene");

    auto font = GameEngine::ResourceManager::GetInstance().LoadFont("/Fonts/RobotoMono-VariableFont_wght.ttf", 100);
    
    glm::vec2 screenSize = m_engine.GetSize();
    glm::vec2 position = {0,0};
    auto canvas = std::make_unique<GameEngine::Canvas>(position,screenSize);

    auto canvasObject = std::make_unique<GameEngine::CanvasObject>();
    canvasObject->GetTransform().SetAnchorPoint(GameEngine::anchorPoint::TopMiddle);
    canvasObject->AddElement<GameEngine::UITextElement>("UIText",font);
    canvasObject->GetTransform().SetSize(100.f,100.f);
    canvas->AddObject(std::move(canvasObject));

    scene->AddCanvas(std::move(canvas));
    
    
    auto TextObject = std::make_unique<GameEngine::GameObject>();
    TextObject->AddComponent<GameEngine::TextComponent>("Hallo", font);
    TextObject->GetTransform().SetPosition({500.f,200.f,0});
    scene->AddObject(std::move(TextObject));


    auto obj = std::make_unique<GameEngine::GameObject>();
    obj->AddComponent<GameEngine::SpriteRenderer>("/images/AllyTemp.png");
    auto moveObject = obj->AddComponent<PlayerMovement>(50);
    obj->GetTransform().SetPosition(400,400,0);
    obj->GetTransform().SetScale(10.f,10.f);

    input.AddCommand(GameEngine::InputKeys::ARROW_LEFT, GameEngine::InputStates::Held
        , std::make_unique<MoveCommand>(moveObject, glm::vec3{-1.f, 0.f, 0.f}));
    input.AddCommand(GameEngine::InputKeys::ARROW_RIGHT, GameEngine::InputStates::Held
        , std::make_unique<MoveCommand>(moveObject, glm::vec3{1.f, 0.f, 0.f}));
    input.AddCommand(GameEngine::InputKeys::ARROW_UP, GameEngine::InputStates::Held
        , std::make_unique<MoveCommand>(moveObject, glm::vec3{0.f, -1.f, 0.f}));
    input.AddCommand(GameEngine::InputKeys::ARROW_DOWN, GameEngine::InputStates::Held
        , std::make_unique<MoveCommand>(moveObject, glm::vec3{0.f, 1.f, 0.f}));

    scene->AddObject(std::move(obj));

    obj = std::make_unique<GameEngine::GameObject>();
    obj->AddComponent<GameEngine::SpriteRenderer>("/images/EnemyTemp.png");
    obj->GetTransform().SetPosition(1200,400,0);
    obj->GetTransform().SetScale(10.f,10.f);
    scene->AddObject(std::move(obj));



    m_engine.SetScene(std::move(scene));
    m_engine.run();
}
