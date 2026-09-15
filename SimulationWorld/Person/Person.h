//
// Created by boeken-work on 9/13/26.
//

#ifndef GAMEENGINE_PERSON_H
#define GAMEENGINE_PERSON_H
#include <memory>
#include <queue>
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

        PersonState* GetCurrentState() {return &m_CurrentState;}
        template<typename T>
        T* GetGoal();
    private:
        void InitStates();
        void InitActions();
        void InitGoals();

        std::unique_ptr<Planner> m_Planner{};
        PersonState m_CurrentState{};

        std::vector<Action*> m_AvailableActions{};
        std::queue<Action*> m_CurrentPath{};

        std::vector<Goal*> m_Goals{};
        Goal* m_CurrentGoal{nullptr};
    public:
        ~Person() override;
    };

    template<typename T>
    T * Person::GetGoal()
    {
        for (Goal* goal : m_Goals) {
            if (T* match = dynamic_cast<T*>(goal)) {
                return match;
            }
        }
        return nullptr;
    }
} // SimWorld

#endif //GAMEENGINE_PERSON_H
