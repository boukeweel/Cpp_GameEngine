#pragma  once
#include "glm/vec2.hpp"

namespace GameEngine 
{
    class Canvas 
    {
    public:
        Canvas();

        void SetSize(glm::vec2 newSize);
        void SetSize(float x, float y);

    private:
        glm::vec2 m_size{200,200};

    public:
        ~Canvas() = default;
        Canvas(const Canvas&) = delete;
        Canvas& operator=(const Canvas&) = delete;
        Canvas(Canvas&&) = delete;
        Canvas& operator=(Canvas&&) = delete;       
    };

}