//
// Created by boeken on 9/12/26.
//

#ifndef SimWorld_PLANNER_H
#define SimWorld_PLANNER_H
#include <memory>
#include <queue>
#include <vector>

#include "Action.h"
#include "Goal.h"

namespace SimWorld {
    struct node {
        PersonalState personalState;
        WorldState worldState;
        Action* actionTaken;
        node* parent;
        int gCost;
        int fCost;
    };

    class Planner {
    public:
        Planner(int maxIterations = 1000);

        [[nodiscard]] std::queue<Action*> Plan(const PersonalState& personalState, const WorldState& worldState,
                                               Goal* goal, const std::vector<std::unique_ptr<Action>>&);
        [[nodiscard]] Goal* GetNewGoal(const PersonalState& personalState, const WorldState& worldState,
                                       const std::vector<std::unique_ptr<Goal>>& goals);

    private:
        bool AreSatisfied(const std::vector<Condition>& conditions,
                          const PersonalState& personalState,
                          const WorldState& worldState) const;
        int CountUnsatisfied(const Goal& goal, const PersonalState& personalState,
                             const WorldState& worldState) const;

        int m_MaxIterations{1000};
    };
}

#endif //SimWorld_PLANNER_H
