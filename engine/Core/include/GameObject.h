#pragma once
#include <algorithm>
#include <memory>
#include <typeindex>
#include <unordered_map>
#include <vector>


namespace GameEngine {

    class Component;
    class Transform;

    class GameObject final {
    public:
        GameObject();

        void Update();
        void FixedUpdate();
        void Render();

        template<class  T, typename... Args> requires std::derived_from<T, Component>
	    T* AddComponent(Args&&... args);
	    template<class  T> requires std::derived_from<T, Component>
	    bool RemoveComponent(T* componentToRemove);
	    template<class  T> requires std::derived_from<T, Component>
	    T* GetComponent();
	    template<class  T> requires std::derived_from<T, Component>
	    std::vector<T*> GetComponents();
	    template<class  T> requires std::derived_from<T, Component>
	    bool HasComponent() const;


        Transform& GetTransform() { return *m_Transform; }
    private:
        std::unique_ptr<Transform> m_Transform;
        std::unordered_map<std::type_index,std::vector<std::unique_ptr<Component>>> m_Components;

    public:
        ~GameObject();
	    GameObject(const GameObject&) = delete;
	    GameObject& operator=(const GameObject&) = delete;
	    GameObject(GameObject&&) = delete;
	    GameObject& operator=(GameObject&&) = delete;
    };

    template <class  T, typename ... Args> requires std::derived_from<T, Component>
    T* GameObject::AddComponent(Args&&... args)
    {
    	const auto key = std::type_index(typeid(T));
        auto newComponent = std::make_unique<T>(this, std::forward<Args>(args)...);
        T* componentPtr = newComponent.get();
        m_Components[key].emplace_back(std::move(newComponent));
        return componentPtr;
    }
    template <class  T> requires std::derived_from<T, Component>
    bool GameObject::RemoveComponent(T* componentToRemove)
    {
    	const auto key = std::type_index(typeid(T));
        auto it = m_Components.find(key);
        if(it == m_Components.end())
            return false;

        auto& vec = it->second;
        auto removeIt = std::remove_if(vec.begin(), vec.end(),
         [componentToRemove](const std::unique_ptr<Component>& c){ return c.get() == componentToRemove; });

        if(removeIt != vec.end())
            return false;

        vec.erase(removeIt, vec.end());
        return true;
    }
    template <class  T> requires std::derived_from<T, Component>
    T* GameObject::GetComponent()
    {
    	const auto key = std::type_index(typeid(T));
        auto it = m_Components.find(key);
        if (it != m_Components.end() && !it->second.empty()) {
            return static_cast<T*>(it->second.front().get());
        }
        return nullptr;
    }
    template <class  T> requires std::derived_from<T, Component>
    std::vector<T*> GameObject::GetComponents()
    {
    	std::vector<T*> result;
        const auto key = std::type_index(typeid(T));
        if(auto it = m_Components.find(key); it != m_Components.end()) {

            result.reserve(it->second.size());
            for (const auto& component : it->second) {
                result.push_back(static_cast<T*>(component.get()));
            }
        }
        return result;
    }
    template <class  T> requires std::derived_from<T, Component>
    bool GameObject::HasComponent() const
    {
    	const auto key = std::type_index(typeid(T));
        auto it = m_Components.find(key);
        return it != m_Components.end() && !it->second.empty();
    }
} 