//
// Created by boeken-work on 9/23/26.
//

#ifndef GAMEENGINE_GOAPAGENTCOMPONENT_H
#define GAMEENGINE_GOAPAGENTCOMPONENT_H
#include <memory>
#include <queue>

#include "Component.h"
#include "States.h"

namespace SimWorld
{
    class Goal;
    class Action;
    class Planner;

    class GOAPAgentComponent : public GameEngine::Component
    {
    public:
        GOAPAgentComponent(GameEngine::GameObject* owner);

        void Begin() override;
        void FixedUpdate() override;

        template<typename T> requires std::derived_from<T, Goal>
        T* GetGoal();

        void AddAction(std::unique_ptr<Action> action);
        void AddGoal(std::unique_ptr<Goal> goal);
        void AddState(PersonKeys, int value);

        void SetState(PersonKeys key, int value);
        const PersonState& GetState() const{return m_CurrentState;}

        ~GOAPAgentComponent() override;
    private:

        ///Checks if the state changes has anything to do with the current goal
        ///if it has nothing to do with the current goal, recalculated the goals to check if the current goal is still
        ///the most important
        void ReCalculatedGoal(PersonKeys key);

        ///Plans the path again, and changes the actions based on the result.
        void ReCalculatedPath();

        std::unique_ptr<Planner> m_Planner{};
        //I am not sure if I should make the agent or the person hold the state but for now this is oke enough
        PersonState m_CurrentState{};

        std::vector<std::unique_ptr<Action>> m_AvailableActions{};
        std::queue<Action*> m_CurrentPath{};

        std::vector<std::unique_ptr<Goal>> m_Goals{};
        Goal* m_CurrentGoal{nullptr};
    };

    template<typename T> requires std::derived_from<T, Goal>
    T * GOAPAgentComponent::GetGoal()
    {
        for (auto& goal : m_Goals) {
            if (T* match = dynamic_cast<T*>(goal.get())) {
                return match;
            }
        }
        return nullptr;
    }
} // SimWorld

#endif //GAMEENGINE_GOAPAGENTCOMPONENT_H
