#ifndef RECT_COLLIDER_COMPONENT_H
#define RECT_COLLIDER_COMPONENT_H
#include <glm/glm.hpp>
#include "BaseColliderComponent.h"
#include "CollisionDataStructures.h"

namespace GameEngine
{

    class RectColliderComponent : public BaseColliderComponent
    {
    public:
        RectColliderComponent(GameObject* owner);
        void GetBounds(float& outMinX, float& outMinY,float& outMaxX, float& outMaxY) const override;

        void SetBounds(float left, float right, float top, float bottom);
    private:
        void SetBoundsToSprite();

        RectShape m_ColliderShape{0.f,1.f,1.f,0.f};
    public:
        ~RectColliderComponent() override = default;
        RectColliderComponent(const RectColliderComponent& other) = delete;
	    RectColliderComponent(RectColliderComponent&& other) = delete;
	    RectColliderComponent& operator=(const RectColliderComponent& other) = delete;
	    RectColliderComponent& operator=(RectColliderComponent&& other) = delete;       
    };
}

#endif
