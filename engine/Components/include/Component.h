#pragma once

namespace GameEngine {

    class GameObject;

    class Component {
    
    public:
        Component(GameObject* owner) : m_Owner(owner) {}

        virtual void Update() {}
        virtual void FixedUpdate() {}
        virtual void Render() {}
        
    private:
        GameObject* m_Owner;

    public:
        virtual ~Component() = default;
        Component(const Component&) = delete;
	    Component& operator=(const Component&) = delete;
	    Component(Component&&) = delete;
	    Component& operator=(Component&&) = delete;
    };
}