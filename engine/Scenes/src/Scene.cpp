#include "Scene.h"
#include "GameObject.h"
#include <algorithm>
#include <memory>
#include <string>
#include <utility>
#include "IBaseScene.h"
#include "CollisionHandler.h"

namespace GameEngine{

    unsigned int Scene::s_idCounter = 0;

    Scene::~Scene()
    {
        m_sceneObjects.clear();
        m_CollisionHandler.reset();
    }

    Scene::Scene(const std::string& name, std::unique_ptr<IBaseScene> load, const SceneContext& sceneContext) 
    : m_name(name), m_id(s_idCounter++), m_Load{ std::move(load) }, m_SceneContext{sceneContext} 
    {
        m_CollisionHandler = std::make_unique<CollisionHandler>();
    }

    void Scene::LoadInScene()
    {
        m_Load->Load(*this);
    }

    bool Scene::AddCanvas(std::unique_ptr<Canvas> canvas)
    {
        if(m_canvas == nullptr)
        {
            m_canvas = std::move(canvas);
            return true;
        }
        return false;
    }
    void Scene::AggressiveAddCanvas(std::unique_ptr<Canvas> canvas)
    {
        RemoveCanvas();
        m_canvas = std::move(canvas);
    }
    std::unique_ptr<Canvas> Scene::RemoveCanvas()
    {
        return std::move(m_canvas);
    }
    bool Scene::HasCanvas()
    {
        return m_canvas != nullptr;
    }
    Canvas* Scene::GetCanvas()
    {
        return m_canvas.get();
    }

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

        //TODO: put this in a seperated update loop, like a collision update loop
        if(m_CollisionHandler != nullptr)
        {
            m_CollisionHandler->FixedUpdate();
        }
    }
    
    void Scene::Update()
    {
    	for(auto& object : m_sceneObjects)
    	{
    		object->Update();
    	}

        if(m_canvas != nullptr)
        {
            m_canvas->Update();
        }


    }
    
    void Scene::Render() const
    {
    	for (const auto& object : m_sceneObjects)
    	{
    		object->Render();
    	}

        if(m_canvas != nullptr)
        {
            m_canvas->Render();
        }

        if(m_CollisionHandler != nullptr)
        {
            m_CollisionHandler->Render();
        }
    }
}