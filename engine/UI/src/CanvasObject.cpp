#include "CanvasObject.h"

namespace GameEngine
{
    CanvasObject::CanvasObject(){}

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