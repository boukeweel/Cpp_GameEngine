#ifndef UI_ELEMENT_H
#define UI_ELEMENT_H

namespace GameEngine
{
    class CanvasObject;

    class UIElement 
    {
    public:
        UIElement(CanvasObject* owner);

        virtual void Update() {};
        virtual void Render() const {};

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

#endif //UI_ELEMENT_H