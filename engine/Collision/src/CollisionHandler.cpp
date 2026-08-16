// ...existing code...
#include "CollisionHandler.h"

namespace GameEngine
{

    CollisionHandler::CollisionHandler(){

    }

    void CollisionHandler::Update()
    {

    }

    void CollisionHandler::RegisterCollider(BaseColliderComponent* collider)
    {
        m_allColliders.emplace_back(collider);
    }

    void CollisionHandler::RemoveCollider(BaseColliderComponent* collider)
    {
        //implement code
    }

} 