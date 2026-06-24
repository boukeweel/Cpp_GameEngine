#include "Transform.h"
#include "GameObject.h"

namespace GameEngine
{
    Transform::Transform(GameObject& owner)
        : m_Owner(&owner)
    {
    }

    void Transform::SetPositionX(float x)
    {
        SetPosition(glm::vec3(x, m_LocalPosition.y, m_LocalPosition.z));
    }

    void Transform::SetPositionY(float y)
    {
        SetPosition(glm::vec3(m_LocalPosition.x, y, m_LocalPosition.z));
    }

    void Transform::SetPositionZ(float z)
    {
        SetPosition(glm::vec3(m_LocalPosition.x, m_LocalPosition.y, z));
    }

    void Transform::SetPosition(float x, float y, float z)
    {
        SetLocalPosition(glm::vec3(x, y, z));
    }

    void Transform::SetPosition(const glm::vec3& position)
    {
        SetPosition(position.x, position.y, position.z);
    }

    glm::vec3 Transform::GetWorldPosition()
    {
        if (GetIsDirtyTransform())
            UpdateWorldPosition();
	    return m_WorldPosition;
    }

    void Transform::UpdateWorldPosition()
    {
        if(GetIsDirtyTransform())
        {
            if(!m_Owner){
                m_WorldPosition = m_LocalPosition;
            }
            else{
                m_WorldPosition = m_LocalPosition + m_Owner->GetTransform().GetWorldPosition();
            }
        }
    }
    
    void Transform::SetLocalPosition(const glm::vec3& position)
    {
        m_LocalPosition = position;
        SetPositionDirty();
    }

    void Transform::SetPositionDirty()
    {
        IsDirty = true;

        //todo recursively set all children dirty
    }

    void Transform::SetRotationX(float angle)
    {
        m_rotation.x = angle;
    }

    void Transform::SetRotation(const glm::vec3& rotation)
    {
        m_rotation = rotation;
    }

    glm::vec3 Transform::GetRotation() const
    {
        return m_rotation;
    }

    void Transform::SetScaleX(float x)
    {
        m_scale.x = x;
    }

    void Transform::SetScaleY(float y)
    {
        m_scale.y = y;
    }

    void Transform::SetScale(float x, float y)
    {
        m_scale = glm::vec2(x, y);
    }

    void Transform::SetScale(const glm::vec2& scale)
    {
        m_scale = scale;
    }

    glm::vec2 Transform::GetScale() const
    {
        return m_scale;
    }
}