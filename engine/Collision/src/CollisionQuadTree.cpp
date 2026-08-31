#include "CollisionQuadTree.h"

#include <iostream>

#include "CollisionHandler.h"
#include "Renderer.h"

namespace GameEngine
{
    CollisionQuadTree::CollisionQuadTree(RectShape shape,int maxColliders,bool drawDebugLines)
    : m_QuadTreeShape(shape), m_MaxColliders{maxColliders}, m_DrawDebugLines{drawDebugLines}
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
            for (auto& collider : m_Colliders)
            {
                InsertIntoDevision(collider);
            }
            m_Colliders.clear();
        }
        InsertIntoDevision(collider);
    }

    void CollisionQuadTree::SubDivide()
    {
        const float midX = (m_QuadTreeShape.Left + m_QuadTreeShape.Right) / 2.f;
        const float midY = (m_QuadTreeShape.Bottom + m_QuadTreeShape.Top) / 2.f;

        RectShape topLeft{m_QuadTreeShape.Left, midX, m_QuadTreeShape.Top, midY};
        m_QuadTrees[0] = std::make_unique<CollisionQuadTree>(topLeft, m_MaxColliders,m_DrawDebugLines);
        RectShape topRight{midX, m_QuadTreeShape.Right, m_QuadTreeShape.Top, midY};
        m_QuadTrees[1] = std::make_unique<CollisionQuadTree>(topRight, m_MaxColliders,m_DrawDebugLines);
        RectShape bottomLeft{m_QuadTreeShape.Left, midX, midY, m_QuadTreeShape.Bottom};
        m_QuadTrees[2] = std::make_unique<CollisionQuadTree>(bottomLeft, m_MaxColliders,m_DrawDebugLines);
        RectShape bottomRight{midX, m_QuadTreeShape.Right, midY, m_QuadTreeShape.Bottom};
        m_QuadTrees[3] = std::make_unique<CollisionQuadTree>(bottomRight, m_MaxColliders,m_DrawDebugLines);

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

    void CollisionQuadTree::Query(RectShape shape,std::unordered_set<BaseColliderComponent*>& outSet)
    {
        if (!Intersects(shape.Left, shape.Bottom, shape.Right, shape.Top))
            return;

        for (auto* collider : m_Colliders)
        {
            float cMinX, cMinY, cMaxX, cMaxY;
            collider->GetBounds(cMinX, cMinY, cMaxX, cMaxY);
            if (!(cMinX > shape.Right || cMaxX < shape.Left ||
                  cMinY > shape.Top  || cMaxY < shape.Bottom))
            {
                outSet.insert(collider);
            }
        }

        if (m_IsSubdivided)
        {
            for (auto& child : m_QuadTrees)
                child->Query(shape, outSet);
        }
    }

    void CollisionQuadTree::SetDrawDebugLines(bool drawDebugLines)
    {
        m_DrawDebugLines = drawDebugLines;
        for (const auto& quadTree : m_QuadTrees)
        {
            if (quadTree)
                quadTree->SetDrawDebugLines(drawDebugLines);
        }
    }

    void CollisionQuadTree::DebugDraw() const
    {
        if (!m_DrawDebugLines) return;

        auto& renderer = Renderer::GetInstance();
        renderer.DrawDebugRect(m_QuadTreeShape, {0, 255, 255, 255});

        if (m_IsSubdivided) {
            for (const auto& quadTree : m_QuadTrees)
            {
                if (quadTree)
                    quadTree->DebugDraw();
            }
        }
    }
}
