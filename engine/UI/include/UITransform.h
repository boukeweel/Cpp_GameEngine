#pragma once
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>

namespace GameEngine 
{
    enum class anchorPoint
    {
        TopLeft = 1,
        TopMiddle = 2,
        TopRight = 3,
        MiddleLeft = 4,
        Middle = 5,
        MiddleRight = 6,
        DownLeft = 7,
        DownMiddle = 8,
        DownRight = 9,
    };

    class CanvasObject;

    class UITransform final 
    {
    public:
        UITransform(CanvasObject& owner);

        void SetLocation(glm::vec2 newLocation);
        void SetLocation(float x, float y);
        void SetDepth(float Depth);
        
        float GetDepth() const;
        glm::vec2 GetLocation() const;

    private:
        CanvasObject* m_owner{nullptr};
    
        
        anchorPoint m_anchorPoint{anchorPoint::TopLeft};
        glm::vec2 m_offset{0.f,0.f};
        glm::vec2 m_resolvedPosition{0.f,0.f}; //calculated when invalid dirty flag
        glm::vec2 m_size{1.f,1.f};
        float depth;

        bool m_isLocationDirty{true};

    public:
        ~UITransform() = default;
        UITransform(const UITransform&) = delete;
        UITransform& operator=(const UITransform&) = delete;
        UITransform(UITransform&&) = delete;
        UITransform& operator=(UITransform&&) = delete;
    };
}
  