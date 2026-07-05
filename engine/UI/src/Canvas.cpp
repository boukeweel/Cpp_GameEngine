#include "Canvas.h"
#include "CanvasObject.h"
#include "glm/ext/vector_float2.hpp"
#include <algorithm>
#include <memory>
#include <utility>



namespace GameEngine
{
    Canvas::Canvas(glm::vec2 size) : m_size{size}
    {}

    Canvas::Canvas(glm::vec2 position, glm::vec2 size) : m_position{position}, m_size{size}
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
            object->Render();
        }
    }

    void Canvas::Update()
    {
        for (auto& object : m_objects) 
        {
            object->Update();
        }
    }

    void Canvas::SetPositionDirty()
    {
        for (auto& object : m_objects)
        {
            object->GetTransform().SetPositionDirty();
        }
    }

    void Canvas::SetSize(glm::vec2 newSize)
    {
        m_size = newSize;
        SetPositionDirty();
    }

    void Canvas::SetSize(float x, float y)
    {
        SetSize({x,y});
    }

    void Canvas::SetPosition(glm::vec2 newPosition)
    {
        m_position = newPosition;
        SetPositionDirty();
    }

    void Canvas::SetPosition(float x, float y)
    {
        SetPosition({x,y});
    }

}