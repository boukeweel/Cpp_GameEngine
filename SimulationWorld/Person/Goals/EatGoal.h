//
// Created by boeken-work on 9/14/26.
//

#ifndef GAMEENGINE_EATGOAL_H
#define GAMEENGINE_EATGOAL_H
#include "../../GOAP/Goal.h"

namespace SimWorld {
    class EatGoal : public Goal
    {
    public:
        EatGoal();

        int DistanceTo(const PersonalState& personalState, const WorldState& worldState) override;

        bool IsPersonalKeyRelated(const PersonalKey& key) override;
    };
} // SimWorld

#endif //GAMEENGINE_EATGOAL_H
