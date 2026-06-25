#include "GameObject.h"
#include "Transform.h"
#include "Component.h"
#include <memory>

namespace GameEngine {

    GameObject::GameObject()
        : m_Transform{std::make_unique<Transform>(*this)}
    {}

    GameObject::~GameObject() = default;

    void GameObject::Update() {
        for (auto& [type, components] : m_Components) {
            for (auto& component : components) {
                component->Update();
            }
        }
    }
    void GameObject::FixedUpdate() {
        for (auto& [type, components] : m_Components) {
            for (auto& component : components) {
                component->FixedUpdate();
            }
        }
    }
    void GameObject::Render() {
        for (auto& [type, components] : m_Components) {
            for (auto& component : components) {
                component->Render();
            }
        }
    }

}