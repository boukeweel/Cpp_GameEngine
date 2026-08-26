#include "CollisionHandler.h"
#include "CollisionQuadTree.h"
#include "CollisionDataStructures.h"
#include <algorithm>

namespace GameEngine
{

    CollisionHandler::CollisionHandler()
    {}

    void CollisionHandler::Update()
    {
        m_QuadTree = std::make_unique<CollisionQuadTree>(RectShape{0,500,500,0}, 1);
        for (auto* collider : m_Colliders)
            m_QuadTree->Insert(collider);
    }

    void CollisionHandler::Render() const
    {
        if (m_QuadTree)
            m_QuadTree->DebugDraw();
    }

    CollisionHandler::~CollisionHandler() {
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