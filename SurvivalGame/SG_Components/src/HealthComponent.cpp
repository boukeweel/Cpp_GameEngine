//
// Created by boeken-work on 9/5/26.
//

#include "HealthComponent.h"

namespace SurvivalGame
{
    HealthComponent::HealthComponent(GameEngine::GameObject* owner, float health) : Component(owner), m_MaxHealth(health), m_CurrentHealth(health)
    {}

    void HealthComponent::TakeDamage(float damageAmount)
    {
        if (damageAmount > m_CurrentHealth) {
            m_OnDeath.Invoke();
            return;
        }

        m_CurrentHealth -= damageAmount;
    }

    void HealthComponent::Heal(float healAmount)
    {
        m_CurrentHealth += healAmount;
        //no clue if this is the correct way
        //it makes sure the current health does not go over the max health
        if (m_CurrentHealth > m_MaxHealth) {
            m_CurrentHealth = m_MaxHealth;
        }
    }

    void HealthComponent::SetHealth(float health)
    {
        m_MaxHealth = health;
        ResetHealth();
    }
}
