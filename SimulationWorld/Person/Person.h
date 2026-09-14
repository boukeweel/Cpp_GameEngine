//
// Created by boeken-work on 9/13/26.
//

#ifndef GAMEENGINE_PERSON_H
#define GAMEENGINE_PERSON_H
#include <memory>
#include <vector>
#include "Component.h"
#include "States.h"

namespace SimWorld {
    class Planner;
    class Goal;
    class Action;

    class Person : public GameEngine::Component {
    public:
        Person(GameEngine::GameObject* owner);

        void FixedUpdate() override;

    private:
        void InitStates();
        void InitActions();
        void InitGoals();

        std::unique_ptr<Planner> m_Planner;
        PersonState m_CurrentState;

        std::vector<Action*> m_AvailableActions;
        std::vector<Action*> m_CurrentPath;

        std::vector<Goal*> m_Goals;
        Goal* CurrentGoal;
    public:
        ~Person();
    };
} // SimWorld

#endif //GAMEENGINE_PERSON_H
