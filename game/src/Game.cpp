#include "Game.h"
#include "GameObject.h"
#include "ResourceManger.h"
#include "Scene.h"
#include "SpriteRenderer.h"
#include <memory>
#include <utility>
#include "TextComponent.h"
#include "Transform.h"

Game::Game(GameEngine::Engine& engine)
    : m_engine(engine) {
}

void Game::run() 
{
    auto scene = std::make_unique<GameEngine::Scene>("Main Scene");

    auto font = GameEngine::ResourceManager::GetInstance().LoadFont("/Fonts/RobotoMono-VariableFont_wght.ttf", 100);
    auto TextObject = std::make_unique<GameEngine::GameObject>();
    TextObject->AddComponent<GameEngine::TextComponent>("Hallo", font);
    TextObject->GetTransform().SetPosition({500.f,200.f,0});
    scene->AddObject(std::move(TextObject));


    auto obj = std::make_unique<GameEngine::GameObject>();
    obj->AddComponent<GameEngine::SpriteRenderer>("/images/AllyTemp.png");

    obj->GetTransform().SetPosition(400,400,0);
    obj->GetTransform().SetScale(10.f,10.f);

    scene->AddObject(std::move(obj));

    obj = std::make_unique<GameEngine::GameObject>();
    obj->AddComponent<GameEngine::SpriteRenderer>("/images/EnemyTemp.png");

    obj->GetTransform().SetPosition(1200,400,0);
    obj->GetTransform().SetScale(10.f,10.f);


    scene->AddObject(std::move(obj));
    m_engine.SetScene(std::move(scene));
    m_engine.run();
}
