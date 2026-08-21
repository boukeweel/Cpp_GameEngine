#include "CollisionQuadTree.h"

#include "CollisionHandler.h"

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
        else
        {
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
    }
    void CollisionQuadTree::SubDivide()
    {
        RectShape topLeft{};
        m_QuadTrees[0] = std::make_unique<CollisionQuadTree>(topLeft, m_MaxColliders);
        RectShape topRight{};
        m_QuadTrees[1] = std::make_unique<CollisionQuadTree>(topRight, m_MaxColliders);
        RectShape bottomLeft{};
        m_QuadTrees[2] = std::make_unique<CollisionQuadTree>(bottomLeft, m_MaxColliders);
        RectShape bottomRight{};
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
}
