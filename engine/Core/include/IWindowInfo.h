#ifndef I_WINDOW_INFO_H
#define I_WINDOW_INFO_H

#include <glm/glm.hpp>

namespace GameEngine
{
    class IWindowInfo
    {
    public:
        virtual ~IWindowInfo() = default;
        virtual glm::vec2 GetSize() const = 0;
        
    };
}

#endif