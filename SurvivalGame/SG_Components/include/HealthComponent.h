//
// Created by boeken-work on 9/5/26.
//

#ifndef GAMEENGINE_HEALTHCOMPONENT_H
#define GAMEENGINE_HEALTHCOMPONENT_H

#include "Component.h"
#include "../../../engine/Core/include/Event.h"

namespace GameEngine {
    class GameObject;
}

namespace SurvivalGame {
    class HealthComponent : public GameEngine::Component
    {
    public:
        HealthComponent(GameEngine::GameObject* owner, float health);

        void TakeDamage(float damageAmount);
        void Heal(float healAmount);

        [[nodiscard]] float GetHealth() const {return m_CurrentHealth;}
        void SetHealth(float health);
        void ResetHealth(){m_CurrentHealth = m_MaxHealth;}

        //I dont like to have the event public, but I am to lazy to find a good fix now
        GameEngine::Event<> m_OnDeath{};
    private:
        float m_CurrentHealth{0};
        float m_MaxHealth{0};
    };
}

#endif //GAMEENGINE_HEALTHCOMPONENT_H
