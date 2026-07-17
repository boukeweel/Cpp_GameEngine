#ifndef CAMERA_H
#define CAMERA_H

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

namespace GameEngine 
{
    class Camera 
    {
    public:
        Camera(const glm::vec2 ScreenSize);

        glm::vec2 WorldToScreen(glm::vec2 worldPos) const;

        void SetPosition(glm::vec2 newPositiion);
        const glm::vec2& GetCameraPosition() const;

    private:
        glm::vec2 m_screenSize;
        glm::vec2 m_cameraPosition;
    public:
        ~Camera() = default;
        Camera(const Camera&) = delete;
        Camera& operator=(const Camera&) = delete;
        Camera(Camera&&) = delete;
        Camera& operator=(Camera&&) = delete;
    };

}

#endif //CAMERA