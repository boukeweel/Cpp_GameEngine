#ifndef BASE_COLLIDER_COMPONENT_H
#define BASE_COLLIDER_COMPONENT_H

#include "Component.h"

namespace GameEngine
{
    enum class ColliderShape
    {
        Rect,
        Circle
    };
    
    class BaseColliderComponent : public Component
    {
    public:
        BaseColliderComponent(GameObject* owner, ColliderShape shape);
        virtual ~BaseColliderComponent();
    
        ColliderShape GetShape() const { return m_Shape; }
    
        virtual void OnCollision(BaseColliderComponent* other) {}
    
        virtual void GetBounds(float& outMinX, float& outMinY,
                                float& outMaxX, float& outMaxY) const = 0;
        
    private:
        ColliderShape m_Shape;
    };
}

#endif