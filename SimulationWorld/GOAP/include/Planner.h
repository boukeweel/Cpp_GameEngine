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
#include "States.h"

namespace SimWorld {
    struct node {
        PersonState goal;
        Action* actionTaken;
        node* parent;
        int gCost;
        int fCost;
    };

    class Planner {
    public:
        Planner(int maxIterations = 1000);

        [[nodiscard]] std::queue<Action*> Plan(const PersonState& currentState, Goal* goal, const std::vector<std::unique_ptr<Action>>&);

    private:
        bool IsSatisfied(const PersonState& GoalState, const PersonState& CurrentState);
        bool IsKeySatisfied(const PersonKeys& key, const int& value, const PersonState& currentState);
        
        int m_MaxIterations{1000};
    };
}

#endif //SimWorld_PLANNER_H
