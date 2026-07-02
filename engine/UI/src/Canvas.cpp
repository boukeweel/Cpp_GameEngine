#include "Canvas.h"
#include "CanvasObject.h"
#include <algorithm>
#include <memory>
#include <utility>



namespace GameEngine
{
    Canvas::Canvas(glm::vec2 size) : m_size{size}
    {}

    void Canvas::AddObject(std::unique_ptr<CanvasObject> object)
    {
        m_objects.emplace_back(std::move(object));
    }

    bool Canvas::RemoveObject(CanvasObject* object)
    {
        //todo implent not sure how to do it anymore, need to serach it up but no wifi :)
        return false;
    }

    void Canvas::Render() const
    {
        for (const auto& object : m_objects) 
        {
            object->Renderer();
        }
    }

    void Canvas::Update()
    {
        for (auto& object : m_objects) 
        {
            object->Update();
        }
    }


}