#include "Camera.h"

namespace GameEngine
{
    Camera::Camera(const glm::vec2 ScreenSize) : m_screenSize(ScreenSize), m_cameraPosition({0,0})
    {
    }

    glm::vec2 Camera::WorldToScreen(glm::vec2 worldPos) const
    {
        glm::vec2 ScreenPos = worldPos - m_cameraPosition;
        ScreenPos.y = m_screenSize.y - ScreenPos.y;
        return ScreenPos;
    }

    void Camera::SetPosition(glm::vec2 newPosition)
    { 
        m_cameraPosition = newPosition; 
    }
    
    const glm::vec2& Camera::GetCameraPosition() const
    {
        return m_cameraPosition;
    }
}