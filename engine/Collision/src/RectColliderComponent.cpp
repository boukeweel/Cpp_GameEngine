#include "RectColliderComponent.h"

#include <iostream>

#include "GameObject.h"
#include "SpriteRenderer.h"
#include "Transform.h"


namespace GameEngine
{
    RectColliderComponent::RectColliderComponent(GameObject* owner) : BaseColliderComponent(owner, ColliderShape::Rect)
    {
        Init();
        SetBoundsToSprite();
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

    void RectColliderComponent::SetBoundsToSprite()
    {
        const auto* sprite = m_Owner->GetComponent<SpriteRenderer>();
        if (sprite == nullptr || sprite->GetTexture() == nullptr)
            return;

        const glm::vec2 textureSize = sprite->GetTexture()->GetSize();
        const glm::vec2 scale = m_Owner->GetTransform().GetScale();
        const glm::vec2 drawSize = textureSize * scale;

        const float halfWidth = drawSize.x * 0.5f;
        const float halfHeight = drawSize.y * 0.5f;

        SetBounds(halfWidth, halfWidth, halfHeight, halfHeight);

        // Move the centered collider to the sprite's center.
        SetOffset({halfWidth, halfHeight, 0.f});
    }
}
