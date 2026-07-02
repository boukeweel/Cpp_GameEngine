#pragma  once

#include "CanvasObject.h"
#include <memory>
#include <sys/types.h>
#include <vector>
#include <glm/vec2.hpp>

namespace GameEngine 
{
    class CanvasObject;

    class Canvas 
    {
    public:
        Canvas(glm::vec2 size = {480,720});

        void Update();
        void Render() const;

        ///Add object to the canvas
        void AddObject(std::unique_ptr<CanvasObject> object);
        ///Return true if able to remove, false if not allowed
        bool RemoveObject(CanvasObject* object);

        //todo: maybe make this a canvas transform or something.
        void SetSize(glm::vec2 newSize);
        void SetSize(float x, float y);

    private:
        glm::vec2 m_size{200,200};
        std::vector<std::unique_ptr<CanvasObject>> m_objects{};

    public:
        ~Canvas() = default;
        Canvas(const Canvas&) = delete;
        Canvas& operator=(const Canvas&) = delete;
        Canvas(Canvas&&) = delete;
        Canvas& operator=(Canvas&&) = delete;       
    };

}