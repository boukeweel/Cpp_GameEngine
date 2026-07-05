#pragma once

namespace GameEngine
{
    class CanvasObject;

    class UIElement 
    {
    public:
        UIElement(CanvasObject* owner);

        virtual void Update();
        virtual void Renderer() const;

    protected:
        CanvasObject* m_owner;
    public:
        virtual ~UIElement() = default;
        UIElement(const UIElement&) = delete;
        UIElement& operator=(const UIElement&) = delete;
        UIElement (UIElement&&) = delete;
        UIElement& operator=(UIElement&&) = delete;
    };
}