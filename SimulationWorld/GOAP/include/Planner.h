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
    class Planner {
    public:
        std::vector<Action*> plan(const PersonState& start, Goal* goal, const std::vector<Action*>& availableActions);
    };
}

#endif //SimWorld_PLANNER_H
