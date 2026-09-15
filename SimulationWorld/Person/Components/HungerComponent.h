//
// Created by boeken-work on 9/15/26.
//

#ifndef GAMEENGINE_HUNGERCOMPONENT_H
#define GAMEENGINE_HUNGERCOMPONENT_H
#include "Component.h"
#include "States.h"

namespace SimWorld
{
    class EatGoal;

    enum class hunger
    {
        fed,
        Hungry,
        starving
    };
    class HungerComponent : public GameEngine::Component
    {
    public:
        HungerComponent(GameEngine::GameObject* owner);

        void FixedUpdate() override;
        void AteFood();
    private:
        void UpdateHunger();

        float HungerTimer{1000};
        float CurrentHungerTimer{0};
        hunger m_Hunger{hunger::fed};
        PersonState* m_CurrentState{nullptr};
        EatGoal* m_EatGoal{nullptr};
    };
} // SimWorld

#endif //GAMEENGINE_HUNGERCOMPONENT_H
