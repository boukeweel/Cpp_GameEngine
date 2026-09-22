//
// Created by boeken on 9/12/26.
//


#include "SimulationScene.h"

#include <memory>

#include "FoodStore.h"
#include "GameObject.h"
#include "HungerComponent.h"
#include "Person.h"
#include "Scene.h"
#include "SpriteRenderer.h"
#include "Transform.h"


namespace SimWorld {
    void SimulationScene::Load(GameEngine::Scene &scene) {
        scene.AddObject(std::move(CreatePerson()));

        auto foodStore = std::make_unique<GameEngine::GameObject>();
        foodStore->AddComponent<FoodStore>(10);
        foodStore->AddComponent<GameEngine::SpriteRenderer>("/Sprites/FoodStore.png");
        foodStore->GetTransform().SetPosition({200,300,0});
        foodStore->GetTransform().SetScale({2,2});
        scene.AddObject(std::move(foodStore));
    }

    std::unique_ptr<GameEngine::GameObject> SimulationScene::CreatePerson()
    {
        auto person = std::make_unique<GameEngine::GameObject>();
        person->AddComponent<HungerComponent>();
        person->AddComponent<Person>();
        person->AddComponent<GameEngine::SpriteRenderer>("/Sprites/Person.png");

        person->GetTransform().SetPosition({500,200,0});

        return std::move(person);
    }
}
