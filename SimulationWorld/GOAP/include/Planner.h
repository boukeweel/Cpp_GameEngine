//
// Created by boeken on 9/12/26.
//

#ifndef SimWorld_PLANNER_H
#define SimWorld_PLANNER_H
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
        Planner(int maxIterations);

        std::vector<Action*> plan(const PersonState& currentState, Goal* goal, const std::vector<Action*>& availableActions);

    private:
        bool IsSatisfied(const PersonState& GoalState, const PersonState& CurrentState);
        std::pair<PersonKeys,int> PickUnsatisfiedKey(const PersonState& GoalState, const PersonState& CurrentState);

        int m_MaxIterations{1000};
    };
}

#endif //SimWorld_PLANNER_H
