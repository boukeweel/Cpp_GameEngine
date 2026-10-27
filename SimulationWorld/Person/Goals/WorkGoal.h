//
// Created by boeken-work on 10/27/26.
//

#ifndef GAMEENGINE_WORKGOAL_H
#define GAMEENGINE_WORKGOAL_H
#include "Goal.h"

namespace SimWorld
{
    class WorkGoal : public Goal
    {
    public:
        WorkGoal();

        int DistanceTo(const PersonalState& personalState, const WorldState& worldState) override;

        bool IsPersonalKeyRelated(const PersonalKey& key) override;
    };
} // SimWorld

#endif //GAMEENGINE_WORKGOAL_H
