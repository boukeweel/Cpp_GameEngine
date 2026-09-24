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
        const PersonalState& GetDesiredPersonalState() const override {return m_DesiredState;}
        const WorldState& GetDesiredWorldState() const override {return m_DesiredWorldState;}

        bool IsPersonalKeyRelated(const PersonalKey& key) override;

        void ChangePriority(int newPriority){m_priority = newPriority;}

    private:
        PersonalState m_DesiredState;
        WorldState m_DesiredWorldState;
    };
} // SimWorld

#endif //GAMEENGINE_EATGOAL_H
