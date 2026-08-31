#ifndef COLLISION_HANDLER_H
#define COLLISION_HANDLER_H

#include <memory>
#include <vector>

#include "CollisionDataStructures.h"

namespace GameEngine
{
    class CollisionQuadTree;
    class BaseColliderComponent;

    class CollisionHandler final
    {
    public:
        CollisionHandler();
        
        void RegisterCollider(BaseColliderComponent* collider);
        void RemoveCollider(BaseColliderComponent* collider);

        [[nodiscard]] const CollisionQuadTree* GetQuadTree() const;

        void Render() const;
        void FixedUpdate();

        void QueryCollision();

    private:
        std::unique_ptr<CollisionQuadTree> m_QuadTree;
        std::vector<BaseColliderComponent*> m_Colliders;

    public:
        ~CollisionHandler();
        CollisionHandler(const CollisionHandler& other) = delete;
	    CollisionHandler(CollisionHandler&& other) = delete;
	    CollisionHandler& operator=(const CollisionHandler& other) = delete;
	    CollisionHandler& operator=(CollisionHandler&& other) = delete;
    };
}

#endif