#pragma once

namespace GameEngine
{
    class CanvasObject;

    class UIElement 
    {
    public:
        UIElement(CanvasObject* owner);

        void Update();
        void Renderer() const;

    protected:
        CanvasObject* m_owner;
    public:
        ~UIElement() = default;
        UIElement(const UIElement&) = delete;
        UIElement& operator=(const UIElement&) = delete;
        UIElement (UIElement&&) = delete;
        UIElement& operator=(UIElement&&) = delete;
    };
}