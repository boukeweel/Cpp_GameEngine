#ifndef COLLISION_HANDLER_H
#define COLLISION_HANDLER_H

#include <memory>
#include <vector>

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
        void Update();

        void Render() const;

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