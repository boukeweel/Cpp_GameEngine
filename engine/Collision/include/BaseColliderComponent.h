#ifndef BASE_COLLIDER_COMPONENT_H
#define BASE_COLLIDER_COMPONENT_H

#include "Component.h"
#include <glm/vec3.hpp>

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
        virtual ~BaseColliderComponent() = default;
    
        ColliderShape GetShape() const { return m_Shape; }
    
        //want to make event system and just have a event you can subscribe to and will do its event thing
        virtual void OnCollision(BaseColliderComponent* other) {}
    
        virtual void GetBounds(float& outMinX, float& outMinY,float& outMaxX, float& outMaxY) const = 0;
        virtual void SetOffset(glm::vec3 offset) {m_Offset = offset;}
    protected:
        glm::vec3 m_Offset{0.f,0.f,0.f};
    private:
        ColliderShape m_Shape;
    };
}

#endif