GetCurrentScene#include "SceneManagar.h"
#include "Scene.h"
#include <iostream>
#include <memory>
#include <algorithm>
#include "IBaseScene.h"

namespace GameEngine
{
    void SceneManagar::FixedUpdate()
    {
        m_Scenes[m_CurrentScene]->FixedUpdate();    
    }

    void SceneManagar::Update()
    {
        m_Scenes[m_CurrentScene]->Update();
    }
    
    void SceneManagar::Render() const
    {
        m_Scenes[m_CurrentScene]->Render();
    }

    void SceneManagar::SetSceneContext(SceneContext SceneContext)
    {
        m_SceneContext = SceneContext;
    }

    Scene& SceneManagar::CreateScene(const std::string& name, std::unique_ptr<IBaseScene> load)
    {
        auto it = std::find_if(m_Scenes.begin(), m_Scenes.end(),
        [&name](const auto& scene) { return scene->GetName() == name; });
        if (it != m_Scenes.end())
        {
            std::cout << "You were trying to create a scene with the name: " << name
               << " but a different scene with the same name already exists\n";
            return **it;
        }

        auto scene = std::unique_ptr<Scene>(new Scene(name, std::move(load),m_SceneContext));
        Scene* rawptr = scene.get();
        m_Scenes.emplace_back(std::move(scene));
        return *rawptr;
    }

    void SceneManagar::LoadScene(unsigned int id)
    {
        m_Scenes[m_CurrentScene]->RemoveAll();
        m_CurrentScene = id;
        m_Scenes[m_CurrentScene]->LoadInScene();
    }

}