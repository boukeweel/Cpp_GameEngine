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
        const std::vector<Condition>& GetPersonalConditions() const override {return m_PersonalConditions;}
        const std::vector<Condition>& GetWorldConditions() const override {return m_WorldConditions;}

        bool IsPersonalKeyRelated(const PersonalKey& key) override;

        void ChangePriority(int newPriority){m_priority = newPriority;}

    private:
        std::vector<Condition> m_PersonalConditions;
        std::vector<Condition> m_WorldConditions;
    };
} // SimWorld

#endif //GAMEENGINE_EATGOAL_H
