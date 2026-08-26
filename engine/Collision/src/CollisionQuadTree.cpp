#include "CollisionQuadTree.h"

#include <iostream>

#include "CollisionHandler.h"
#include "Renderer.h"

namespace GameEngine
{
    CollisionQuadTree::CollisionQuadTree(RectShape shape,int maxColliders): m_QuadTreeShape(shape), m_MaxColliders{maxColliders}
    {
        m_Colliders.reserve(maxColliders);
    }

    void CollisionQuadTree::Insert(BaseColliderComponent* collider)
    {
        //Check if this collider is even in his range
        float minX, minY, maxX, maxY;
        collider->GetBounds(minX, minY, maxX, maxY);

        if (!Intersects(minX, minY, maxX, maxY))
            return;

        //if its already subdiveded it can easily just put it in one of the subdevisions
        if (m_IsSubdivided)
        {
            InsertIntoDevision(collider);
            return;
        }

        if (m_Colliders.size() < m_MaxColliders)
        {
            m_Colliders.emplace_back(collider);
            return;
        }

        if (!m_IsSubdivided)
        {
            SubDivide();
            //Insert all colliders from this quadtree into the subdevisions
            for (auto& collider : m_Colliders)
            {
                InsertIntoDevision(collider);
            }
        }
        InsertIntoDevision(collider);
    }
    void CollisionQuadTree::SubDivide()
    {
        const float midX = (m_QuadTreeShape.Left + m_QuadTreeShape.Right) / 2.f;
        const float midY = (m_QuadTreeShape.Bottom + m_QuadTreeShape.Top) / 2.f;

        RectShape topLeft{m_QuadTreeShape.Left, midX, m_QuadTreeShape.Top, midY};
        m_QuadTrees[0] = std::make_unique<CollisionQuadTree>(topLeft, m_MaxColliders);
        RectShape topRight{midX, m_QuadTreeShape.Right, m_QuadTreeShape.Top, midY};
        m_QuadTrees[1] = std::make_unique<CollisionQuadTree>(topRight, m_MaxColliders);
        RectShape bottomLeft{m_QuadTreeShape.Left, midX, midY, m_QuadTreeShape.Bottom};
        m_QuadTrees[2] = std::make_unique<CollisionQuadTree>(bottomLeft, m_MaxColliders);
        RectShape bottomRight{midX, m_QuadTreeShape.Right, midY, m_QuadTreeShape.Bottom};
        m_QuadTrees[3] = std::make_unique<CollisionQuadTree>(bottomRight, m_MaxColliders);

        m_IsSubdivided = true;
    }

    void CollisionQuadTree::InsertIntoDevision(BaseColliderComponent* collider) const
    {
        for (auto& quadTree : m_QuadTrees) {
            quadTree->Insert(collider);
        }
    }

    bool CollisionQuadTree::Intersects(float minX, float minY, float maxX, float maxY) const
    {
        return !(minX > m_QuadTreeShape.Right  ||
                 maxX < m_QuadTreeShape.Left   ||
                 minY > m_QuadTreeShape.Top    ||
                 maxY < m_QuadTreeShape.Bottom);
    }

    void CollisionQuadTree::DebugDraw() const
    {
        auto& renderer = Renderer::GetInstance();
        renderer.DrawDebugRect(m_QuadTreeShape, {0, 255, 0, 255});

        if (m_IsSubdivided) {
            for (const auto& quadTree : m_QuadTrees)
            {
                if (quadTree)
                    quadTree->DebugDraw();
            }
        }
    }
}
