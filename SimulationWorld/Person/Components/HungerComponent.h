//
// Created by boeken-work on 9/15/26.
//

#ifndef GAMEENGINE_HUNGERCOMPONENT_H
#define GAMEENGINE_HUNGERCOMPONENT_H
#include "Component.h"
#include "../../GOAP/States.h"

namespace SimWorld
{
    class GOAPAgentComponent;
    class EatGoal;
    class Person;

    enum class HungerLevel : int
    {
        fed = 0,
        Hungry = 1,
        starving = 1,
    };
    class HungerComponent : public GameEngine::Component
    {
    public:
        HungerComponent(GameEngine::GameObject* owner);

        void Begin() override;

        void FixedUpdate() override;
        void AteFood();
    private:
        void UpdateHunger();

        float HungerTimer{10};
        float CurrentHungerTimer{0};
        HungerLevel m_Hunger{HungerLevel::fed};
        GOAPAgentComponent* m_GoapAgent{nullptr};
        EatGoal* m_EatGoal{nullptr};
    };
} // SimWorld

#endif //GAMEENGINE_HUNGERCOMPONENT_H
