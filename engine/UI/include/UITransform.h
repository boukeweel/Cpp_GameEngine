#pragma once
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>

namespace GameEngine 
{
    class CanvasObject;

    class UITransform final 
    {
    public:
        UITransform(CanvasObject& owner);

        void SetLocation(glm::vec2 newLocation);
        void SetLocation(float x, float y);
        void SetDepth(float Depth);
        
        float GetDepth() const {return m_canvasLocation.z;}
        glm::vec2 GetLocation() const { return m_canvasLocation; }

    private:
        CanvasObject* m_owner{nullptr};
        
        glm::vec3 m_localLocation{0.f,0.f,0.f};
        glm::vec3 m_canvasLocation{0.f,0.f,0.f};
        float m_rotation = 0;

        bool m_isLocationDirty{true};

    public:
        ~UITransform() = default;
        UITransform(const UITransform&) = delete;
        UITransform& operator=(const UITransform&) = delete;
        UITransform(UITransform&&) = delete;
        UITransform& operator=(UITransform&&) = delete;
    };
}
  