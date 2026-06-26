#include "Scene.h"
#include "GameObject.h"
#include <algorithm>
#include <memory>
#include <string>


namespace GameEngine{

    Scene::Scene(const std::string& name) : m_name{name}
    {}

    void Scene::AddObject(std::unique_ptr<GameObject> object)
    {
        m_sceneObjects.emplace_back(std::move(object));
    }

    void Scene::RemoveObject(std::unique_ptr<GameObject> object)
    {
        m_sceneObjects.erase(std::remove(m_sceneObjects.begin(), m_sceneObjects.end(), object),m_sceneObjects.end());
    }

    void Scene::RemoveAll()
    {
        m_sceneObjects.clear();
    }

    void Scene::FixedUpdate()
    {
    	for (auto& object : m_sceneObjects)
    	{
    		object->FixedUpdate();
    	}
    }
    
    void Scene::Update()
    {
    	for(auto& object : m_sceneObjects)
    	{
    		object->Update();
    	}
    }
    
    void Scene::Render() const
    {
    	for (const auto& object : m_sceneObjects)
    	{
    		object->Render();
    	}
    }
}