//
// Created by boeken on 9/12/26.
//


#include "SimulationScene.h"

#include <memory>

#include "GameObject.h"
#include "Person.h"
#include "Scene.h"

namespace SimWorld {
    void SimulationScene::Load(GameEngine::Scene &scene) {

        auto person = std::make_unique<GameEngine::GameObject>();
        person->AddComponent<Person>();
        scene.AddObject(std::move(person));
    }
}
