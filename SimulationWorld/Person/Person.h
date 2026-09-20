//
// Created by boeken-work on 9/13/26.
//

#ifndef GAMEENGINE_PERSON_H
#define GAMEENGINE_PERSON_H
#include <memory>
#include <queue>
#include <vector>
#include "Component.h"
#include "Event.h"
#include "States.h"

namespace SimWorld {
    class Planner;
    class Goal;
    class Action;

    class Person : public GameEngine::Component {
    public:
        Person(GameEngine::GameObject* owner);
        void Begin() override;

        void FixedUpdate() override;

        //PersonState* GetCurrentState() {return &m_CurrentState;}
        template<typename T> requires std::derived_from<T, Goal>
        T* GetGoal();

        void SetState(PersonKeys key, int value);
    private:
        void InitStates();
        void InitActions();
        void InitGoals();

        ///Checks if the state changes has anything to do with the current goal
        ///if it has nothing to do with the current goal, recalculated the goals to check if the current goal is still
        ///the most important
        void ReCalculatedGoal(PersonKeys key);

        ///Plans the path again, and changes the actions based on the result.
        void ReCalculatedPath();

        std::unique_ptr<Planner> m_Planner{};
        PersonState m_CurrentState{};

        std::vector<std::unique_ptr<Action>> m_AvailableActions{};
        std::queue<Action*> m_CurrentPath{};

        std::vector<std::unique_ptr<Goal>> m_Goals{};
        Goal* m_CurrentGoal{nullptr};
    public:
        ~Person() override;
    };

    template<typename T> requires std::derived_from<T, Goal>
    T * Person::GetGoal()
    {
        for (auto& goal : m_Goals) {
            if (T* match = dynamic_cast<T*>(goal.get())) {
                return match;
            }
        }
        return nullptr;
    }
} // SimWorld

#endif //GAMEENGINE_PERSON_H
