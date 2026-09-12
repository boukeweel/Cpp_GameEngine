#include "BaseColliderComponent.h"
#include "SceneManagar.h"
#include "Scene.h"
#include "CollisionHandler.h"
#include "IBaseScene.h"

namespace GameEngine
{
    BaseColliderComponent::BaseColliderComponent(GameObject* parent, ColliderShape shape) : Component(parent), m_Shape(shape)
    {
        auto& sceneManagar = SceneManagar::GetInstance();
        auto& scene = sceneManagar.GetCurrentScene();
        m_CollisionHandler = scene.GetCollisionHandler();
    }

    BaseColliderComponent::~BaseColliderComponent()
    {
        if (m_CollisionHandler != nullptr)
            m_CollisionHandler->RemoveCollider(this);
    }

    std::size_t BaseColliderComponent::SubscribeToCollision(std::function<void(BaseColliderComponent *)> callback)
    {
        return m_OnCollision.Subscribe(std::move(callback));
    }

    void BaseColliderComponent::UnsubscribeFromCollision(std::size_t id)
    {
        m_OnCollision.Unsubscribe(id);
    }

    void BaseColliderComponent::Init()
    {

        if (m_CollisionHandler != nullptr)
            m_CollisionHandler->RegisterCollider(this);
    }
}
