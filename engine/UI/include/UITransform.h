#ifndef UI_TRANSFORM_H
#define UI_TRANSFORM_H

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
        //not sure if this is the correct way, but now only the canvas can see,
        //SetPositionDirty(), and I for now rather not give acces to everyone to that function.
        friend class Canvas;
    public:
        UITransform(CanvasObject& owner);
        UITransform(CanvasObject& owner, glm::vec2 offset, glm::vec2 size, float depth);

        void SetLocation(float x, float y);        
        void SetLocation(const glm::vec2& newLocation);
        glm::vec2 GetLocation();
        
        void SetDepth(float Depth);
        float GetDepth() const {return m_depth;}
        
        void SetAnchorPoint(anchorPoint newAngerPoint);
        anchorPoint GetAnchorPoint() const {return m_anchorPoint;}
        
        void SetSize(float x, float y);
        void SetSize(const glm::vec2& newSize);
        glm::vec2 GetSize() const {return m_size;}

        
    private:
        void UpdateResolvedPosition();
        void SetPositionDirty();

        glm::vec2 GetAnchorCords();

        CanvasObject* m_owner{nullptr};
    
        anchorPoint m_anchorPoint{anchorPoint::TopLeft};
        glm::vec2 m_offset{0.f,0.f};
        glm::vec2 m_resolvedPosition{0.f,0.f}; //calculated when invalid dirty flag
        glm::vec2 m_size{1.f,1.f};
        float m_depth;

        bool m_isLocationDirty{true};

    public:
        ~UITransform() = default;
        UITransform(CanvasObject& owner, UITransform& otherTransform);
        UITransform& operator=(const UITransform&) = delete;
        UITransform(UITransform&&) = delete;
        UITransform& operator=(UITransform&&) = delete;
    };

    
}
 
#endif //UI_TRANSFORM_H