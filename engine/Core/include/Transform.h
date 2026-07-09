#pragma once
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>

namespace GameEngine {

    class GameObject; 

    class Transform  final 
    {
    public:
        Transform(GameObject& owner);

        void SetPositionX(float x);
        void SetPositionY(float y);
        void SetPositionZ(float z);
        void SetPosition(float x, float y, float z);
        void SetPosition(const glm::vec3& position);
        glm::vec3 GetWorldPosition();
        
        void SetRotationX(float angle);
        void SetRotation(const glm::vec3& rotation);
        glm::vec3 GetRotation() const;

        void SetScaleX(float x);
        void SetScaleY(float y);
        void SetScale(float x, float y);
        void SetScale(const glm::vec2& scale);
        glm::vec2 GetScale() const;

        bool GetIsDirtyTransform() const { return IsDirty; }

        void Translate(const glm::vec3& translation);
        void Translate(const glm::vec2& translation);

    private:
        void UpdateWorldPosition();
        void SetLocalPosition(const glm::vec3& position);
        void SetPositionDirty();

        glm::vec3 m_LocalPosition{ 0.0f, 0.0f, 0.0f };
        glm::vec3 m_WorldPosition{ 0.0f, 0.0f, 0.0f };
        glm::vec3 m_rotation{ 0.0f, 0.0f, 0.0f };
        glm::vec2 m_scale{ 1.0f, 1.0f };

        bool IsDirty{ true };

        GameObject* m_Owner;

    public:
    	~Transform() = default;
    	Transform(const Transform&) = delete;
    	Transform& operator=(const Transform&) = delete;
    	Transform(Transform&&) = delete;
    	Transform& operator=(Transform&&) = delete;

    };

}