#pragma once
#include <memory>


namespace GameEngine {

    class Transform;

    class GameObject final {
    public:
        Transform& GetTransform() { return *m_Transform; }
    private:
        std::unique_ptr<Transform> m_Transform;

    };

}