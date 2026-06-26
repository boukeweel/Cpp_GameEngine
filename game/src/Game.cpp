#include "Game.h"
#include "GameObject.h"
#include "Scene.h"
#include "SpriteRenderer.h"
#include <memory>
#include <utility>
#include "Transform.h"

Game::Game(GameEngine::Engine& engine)
    : m_engine(engine) {
}

void Game::run() 
{
    auto scene = std::make_unique<GameEngine::Scene>("Main Scene");

    auto obj = std::make_unique<GameEngine::GameObject>();
    obj->AddComponent<GameEngine::SpriteRenderer>("/images/Boeken_lol.png");

    obj->GetTransform().SetPosition(0,0,0);
    obj->GetTransform().SetScale(0.5f,0.5f);

    scene->AddObject(std::move(obj));
    m_engine.SetScene(std::move(scene));
    m_engine.run();
}
