#include "CanvasObject.h"
#include "UITransform.h"
#include <memory>

namespace GameEngine
{
    CanvasObject::CanvasObject(){}
    CanvasObject::CanvasObject(UITransform& transfrom)
    : m_transform{std::make_unique<UITransform>(*this,transfrom)} 
    {}

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
                element->Update();
            }
        }
    }

}