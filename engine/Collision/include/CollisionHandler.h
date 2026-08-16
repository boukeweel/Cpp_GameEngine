#ifndef COLLISION_HANDLER_H
#define COLLISION_HANDLER_H

#include <vector>

namespace GameEngine
{
    class BaseColliderComponent;

    class CollisionHandler final
    {
    public:
        CollisionHandler();
        
        void RegisterCollider(BaseColliderComponent* collider);
        void RemoveCollider(BaseColliderComponent* collider);
        void Update();

    private:
        std::vector<BaseColliderComponent*> m_allColliders;

    public:
        ~CollisionHandler() = default;
        CollisionHandler(const CollisionHandler& other) = delete;
	    CollisionHandler(CollisionHandler&& other) = delete;
	    CollisionHandler& operator=(const CollisionHandler& other) = delete;
	    CollisionHandler& operator=(CollisionHandler&& other) = delete;
    };
}

#endif