#include "CanvasObject.h"
#include "Canvas.h"
#include "UITransform.h"
#include <memory>

namespace GameEngine
{
    CanvasObject::CanvasObject() : m_transform{std::make_unique<UITransform>(*this)}
    {}
    CanvasObject::CanvasObject(UITransform& transfrom)
    : m_transform{std::make_unique<UITransform>(*this,transfrom)} 
    {}
    CanvasObject::CanvasObject(anchorPoint anchorPoint, glm::vec2 offset, glm::vec2 size, float depth)
    : m_transform{std::make_unique<UITransform>(*this,offset,size,depth)} 
    {}

    void CanvasObject::AsignCanvas(Canvas& canvas)
    {
        m_pParent = &canvas;
    }

    void CanvasObject::Update()
    {
        for (auto& [type, elements] : m_elements) {
            for (auto& element : elements) {
                element->Update();
            }
        }
    }

    void CanvasObject::Render() const
    {
        for (auto& [type, elements] : m_elements) {
            for (auto& element : elements) {
                element->Render();
            }
        }
    }

}