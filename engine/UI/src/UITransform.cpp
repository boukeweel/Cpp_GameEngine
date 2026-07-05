#include "UITransform.h"
#include <glm/vec2.hpp>
#include "CanvasObject.h"
#include "Canvas.h"

namespace GameEngine 
{
    UITransform::UITransform(CanvasObject& owner) : m_owner{&owner}{}

    UITransform::UITransform(CanvasObject& owner, UITransform& otherTransform) 
    : m_owner{&owner}, m_anchorPoint{otherTransform.GetAnchorPoint()}, m_offset{otherTransform.GetLocation()}
    , m_size{otherTransform.GetSize()}, m_depth{otherTransform.GetDepth()}
    {}
    UITransform::UITransform(CanvasObject& owner, glm::vec2 offset, glm::vec2 size, float depth) 
        : m_owner{&owner},m_offset{offset},m_size{size},m_depth{depth}
    {}

    void UITransform::UpdateResolvedPosition()
    {
        Canvas& canvas = m_owner->GetParentCanvas();

        glm::vec2 canvasPos = canvas.GetPosition();
        glm::vec2 canvasSize = canvas.GetSize();

        glm::vec2 anchorInPixels = canvasPos + (canvasSize * GetAnchorCords());
        m_resolvedPosition = anchorInPixels + m_offset;
    }

    glm::vec2 UITransform::GetAnchorCords()
    {
        switch (m_anchorPoint)
        {
        case anchorPoint::TopLeft:
            return {0,0};
            break;
        
        case anchorPoint::TopMiddle:
            return {0.5,0};
            break;
        
        case anchorPoint::TopRight:
            return {1,0};
            break;
        
        case anchorPoint::MiddleLeft:
            return {0,0.5};
            break;
        
        case anchorPoint::Middle:
            return {0.5,0.5};
            break;
        
        case anchorPoint::MiddleRight:
            return {1,0.5};
            break;
        
        case anchorPoint::DownLeft:
            return {0,1};
            break;
        
        case anchorPoint::DownMiddle:
            return {0.5,1};
            break;
        
        case anchorPoint::DownRight:
            return {1,1};
            break;
        default:
            return {0,0};
            break;
        }

    }

    void UITransform::SetPositionDirty()
    {
        m_isLocationDirty = true;
        //todo
        //When chidlren system is implemented
        //Set Children postition dirty aswell
        //with recursive function
    }

    void UITransform::SetLocation(float x, float y)
    {
        SetLocation({x,y});
    }

    void UITransform::SetLocation(const glm::vec2& newOffset)
    {
        m_offset = newOffset;
        SetPositionDirty();
    }

    glm::vec2 UITransform::GetLocation()
    {
        if(m_isLocationDirty)
            UpdateResolvedPosition();
        return m_resolvedPosition;
    }

    void UITransform::SetDepth(float newDepth)
    {
        m_depth = newDepth;
        SetPositionDirty();
    }

    void UITransform::SetAnchorPoint(anchorPoint newAnchorPoint) 
    {
        m_anchorPoint = newAnchorPoint;
        SetPositionDirty();
    }

    void UITransform::SetSize(float x, float y)
    {
        SetSize({x,y});
    }

    void UITransform::SetSize(const glm::vec2& newSize)
    {
        m_size = newSize;
    }
}