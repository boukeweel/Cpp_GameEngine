#ifndef TEST_SCENE_H
#define TEST_SCENE_H

#include "IBaseScene.h"
#include "Scene.h"

class TestScene : public GameEngine::IBaseScene
{
    void Load(GameEngine::Scene& scene) override;
};

#endif