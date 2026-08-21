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
        
        scene.GetCollisionHandler()->RegisterCollider(this);
    }

}