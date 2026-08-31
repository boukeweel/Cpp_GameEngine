#ifndef BASE_COLLIDER_COMPONENT_H
#define BASE_COLLIDER_COMPONENT_H

#include "Component.h"
#include <glm/vec3.hpp>
#include "Event.h"

namespace GameEngine
{
    class CollisionHandler;

    enum class ColliderShape
    {
        Rect,
        Circle
    };
    
    class BaseColliderComponent : public Component
    {
    public:
        BaseColliderComponent(GameObject* owner, ColliderShape shape);

        ~BaseColliderComponent() override;
    
        ColliderShape GetShape() const { return m_Shape; }

        virtual void GetBounds(float& outMinX, float& outMinY,float& outMaxX, float& outMaxY) const = 0;
        virtual void SetOffset(glm::vec3 offset) {m_Offset = offset;}

        Event<BaseColliderComponent*> OnCollision;
    protected:
        glm::vec3 m_Offset{0.f,0.f,0.f};

        virtual void Init();
    private:
        ColliderShape m_Shape;
        CollisionHandler* m_CollisionHandler;


    };
}

#endif