#include "CollisionHandler.h"
#include "CollisionQuadTree.h"
#include "CollisionDataStructures.h"
#include <algorithm>
#include <iostream>

#include "Renderer.h"

namespace GameEngine
{

    CollisionHandler::CollisionHandler()
    {
        m_QuadTree = std::make_unique<CollisionQuadTree>(RectShape{0,1280.f,720.f,0}, 2, true);
    }
    CollisionHandler::~CollisionHandler() = default;

    const CollisionQuadTree* CollisionHandler::GetQuadTree() const
    {
        return m_QuadTree.get();
    }

    void CollisionHandler::Render() const
    {
        if (m_QuadTree)
            m_QuadTree->DebugDraw();
    }

    void CollisionHandler::FixedUpdate()
    {
        m_QuadTree->Clear();
        for (auto* collider : m_Colliders)
            m_QuadTree->Insert(collider);

        QueryCollision();
    }

    //todo actualy handle the Gotten colliders and check for near collision check
    void CollisionHandler::QueryCollision()
    {
        for (auto* collider : m_Colliders)
        {
            RectShape shape;
            collider->GetBounds(shape.Left,shape.Bottom,shape.Right,shape.Top);
            std::unordered_set<BaseColliderComponent*> foundColliders;
            m_QuadTree->Query(shape,foundColliders);

            for (auto found_collider: foundColliders) {
                if (found_collider == collider)
                    continue;

                collider->OnCollision.Invoke(found_collider);
            }
        }
    }

    void CollisionHandler::RegisterCollider(BaseColliderComponent* collider)
    {
        m_Colliders.emplace_back(collider);
    }

    void CollisionHandler::RemoveCollider(BaseColliderComponent* collider)
    {
        m_Colliders.erase(
            std::remove(m_Colliders.begin(), m_Colliders.end(), collider),
            m_Colliders.end());
    }
} 