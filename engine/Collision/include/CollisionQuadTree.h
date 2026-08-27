#ifndef GAMEENGINE_COLLISION_QUADTREE_H
#define GAMEENGINE_COLLISION_QUADTREE_H
#include "RectColliderComponent.h"
#include <vector>
#include <array>
#include <memory>

namespace GameEngine {
    class BaseColliderComponent;

    class CollisionQuadTree
    {
    public:
        CollisionQuadTree(RectShape shape,int maxColliders,bool drawDebugLines=false);

        void Insert(BaseColliderComponent* collider);

        void SetDrawDebugLines(bool drawDebugLines);

        void DebugDraw() const;

    private:
        void SubDivide();
        void InsertIntoDevision(BaseColliderComponent* collider) const;
        bool Intersects(float minX, float minY, float maxX, float maxY) const;


        RectShape m_QuadTreeShape{0,0,0,0};
        int m_MaxColliders{5};
        std::vector<BaseColliderComponent*> m_Colliders{};
        bool m_IsSubdivided{false};

        bool m_DrawDebugLines{false};

        std::array<std::unique_ptr<CollisionQuadTree>, 4> m_QuadTrees{};

    };
}

#endif //GAMEENGINE_COLLISION_QUADTREE_H
