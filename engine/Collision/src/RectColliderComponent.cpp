#include "RectColliderComponent.h"
#include "GameObject.h"
#include "Transform.h"

namespace GameEngine
{
    RectColliderComponent::RectColliderComponent(GameObject* owner) : BaseColliderComponent(owner, ColliderShape::Rect)
    {
        Init();
    }

    void RectColliderComponent::GetBounds(float& outMinX, float& outMinY, float& outMaxX, float& outMaxY) const
    {
        glm::vec3 ownerPosition = m_Owner->GetTransform().GetWorldPosition();
        glm::vec3 colliderPosition = ownerPosition + m_Offset;

        outMinX = colliderPosition.x - m_ColliderShape.Left;
        outMaxX = colliderPosition.x + m_ColliderShape.Right;
        outMinY = colliderPosition.y - m_ColliderShape.Bottom;
        outMaxY = colliderPosition.y + m_ColliderShape.Top;
    }

    void RectColliderComponent::SetBounds(float left, float right, float top, float bottom)
    {
        m_ColliderShape.Left = left;
        m_ColliderShape.Right = right;
        m_ColliderShape.Top = top;
        m_ColliderShape.Bottom = bottom;
    }
}
