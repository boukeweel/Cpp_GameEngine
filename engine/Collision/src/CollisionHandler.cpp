#include "CollisionHandler.h"
#include "CollisionQuadTree.h"
#include "CollisionDataStructures.h"
#include <algorithm>
#include <iostream>

#include "Renderer.h"

namespace GameEngine
{

    CollisionHandler::CollisionHandler() = default;
    CollisionHandler::~CollisionHandler() = default;

    void CollisionHandler::Update()
    {
        //Bad
        m_QuadTree = std::make_unique<CollisionQuadTree>(RectShape{0,1280.f,720.f,0}, 2, true);
        for (auto* collider : m_Colliders)
            m_QuadTree->Insert(collider);

    }

    const CollisionQuadTree* CollisionHandler::GetQuadTree() const
    {
        return m_QuadTree.get();
    }

    void CollisionHandler::Render() const
    {
        if (m_QuadTree)
            m_QuadTree->DebugDraw();
    }

    //todo actualy handle the Gotten colliders and check for near collision check
    void CollisionHandler::QueryCollision()
    {
        std::unordered_set<BaseColliderComponent*> colliders;
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