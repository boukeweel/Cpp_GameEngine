#ifndef GAMEENGINE_COLLISION_QUADTREE_H
#define GAMEENGINE_COLLISION_QUADTREE_H
#include "RectColliderComponent.h"
#include <vector>
#include <array>
#include <memory>
#include <unordered_set>

namespace GameEngine {
    class BaseColliderComponent;

    class CollisionQuadTree
    {
    public:
        CollisionQuadTree(RectShape shape,int maxColliders,bool drawDebugLines=false);

        void Insert(BaseColliderComponent* collider);

        ///Searches for the colliders inside the quadtree what are contained in given shape
        ///This function will check every instance of the children quadtrees inside it
        ///Shape: the place where it will gather and return all the variable
        ///outVector: all the colliders that where inside of the shape
        void Query(RectShape shape,std::unordered_set<BaseColliderComponent*>& outSet);

        void SetDrawDebugLines(bool drawDebugLines);
        void DebugDraw() const;

        void Clear();

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
