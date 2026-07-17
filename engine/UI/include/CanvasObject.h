#ifndef CANVAS_OBJECT_H
#define CANVAS_OBJECT_H

#include <algorithm>
#include <concepts>
#include <memory>
#include <typeindex>
#include <unordered_map>
#include <utility>
#include <vector>
#include "UIElement.h"
#include "UITransform.h"


namespace GameEngine 
{
    //Ask chat when back if there is a way to make a base class for this and gameobject,
    //where the componenet system works the same but it just checks for gameobject if base = Component, and same for this

    class Canvas;

    class CanvasObject final 
    {
    public:
        CanvasObject();
        CanvasObject(UITransform& transform);
        CanvasObject(anchorPoint anchorPoint, glm::vec2 offset, glm::vec2 size = {1.f,1.f}, float depth = 0);

        void Update();
        void Render() const;

        void AsignCanvas(Canvas& canvas);

        [[nodiscard]] UITransform& GetTransform() const {return *m_transform;}
        [[nodiscard]] Canvas& GetParentCanvas() const {return *m_pParent;}

        template<class T, typename... Args> requires std::derived_from<T, UIElement>
        T* AddElement(Args&&... args);
        template<class T> requires std::derived_from<T, UIElement>
        bool RemoveElement(T* ElementToRemove);
        template<class T> requires std::derived_from<T, UIElement>
        T* GetElement();
        template<class T> requires std::derived_from<T, UIElement>
        std::vector<T*> GetElements();
        template<class T> requires std::derived_from<T, UIElement>
        bool HasComponent() const;

    private:
        std::unique_ptr<UITransform> m_transform;
        std::unordered_map<std::type_index, std::vector<std::unique_ptr<UIElement>>> m_elements;

        Canvas* m_pParent;
    
    public:
        ~CanvasObject() = default;
        CanvasObject(const CanvasObject&) = delete;
        CanvasObject& operator=(const CanvasObject&) = delete;
        CanvasObject(CanvasObject&&) = delete;
        CanvasObject& operator=(CanvasObject&&) = delete;
    };

    template<class T, typename... Args> requires std::derived_from<T, UIElement>
    T* CanvasObject::AddElement(Args&&... args)
    {
        const auto key = std::type_index(typeid(T));
        auto newComponent = std::make_unique<T>(this, std::forward<Args>(args)...);
        T* componentptr = newComponent.get();
        m_elements[key].emplace_back(std::move(newComponent));
        return componentptr;
    }

    template<class T> requires std::derived_from<T, UIElement>
    bool CanvasObject::RemoveElement(T* ElementToRemove)
    {
        const auto key = std::type_index(typeid(T));
        auto it = m_elements.find(key);
        if(it == m_elements.end())
            return false;

        auto& vec = it->second;
        auto removeIt = std::remove_if(vec.begin(),vec.end(),[ElementToRemove](const std::unique_ptr<UIElement>& c){return c == ElementToRemove;});

        if(removeIt == vec.end())
            return false;

        vec.erase(removeIt,vec.begin());
        return true;
    }

    template<class T> requires std::derived_from<T, UIElement>
    T* CanvasObject::GetElement()
    {
        const auto key = std::type_index(typeid(T));
        auto it = m_elements.find(key);
        if(it != m_elements.end() && !it->second.empty())
        {
            return static_cast<T*>(it->second.front().get());
        }
        return nullptr;
    }
    template<class T> requires std::derived_from<T, UIElement>
    std::vector<T*> CanvasObject::GetElements()
    {
        std::vector<T*> result;
        const auto key = std::type_index(typeid(T));
        auto it = m_elements.find(key);
        if(it != m_elements.end())
        {
            result.reserve(it->second.size());
            for(const auto& elements : it->second)
            {
                result.emplace_back(static_cast<T*>(elements.get()));
            }
        }
    }
    template<class T> requires std::derived_from<T, UIElement>
    bool CanvasObject::HasComponent() const
    {
        const auto key = std::type_index(typeid(T));
        auto it = m_elements.find(key);
        return it != m_elements.end() && !it->second.empty();
    }
}

#endif //CANVAS_OBJECT_H