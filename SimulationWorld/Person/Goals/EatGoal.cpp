//
// Created by boeken-work on 9/14/26.
//

#include "EatGoal.h"

namespace SimWorld {
    EatGoal::EatGoal() : Goal(10)
    {
        m_PersonalConditions.push_back({
            StateValue::Personal(PersonalKey::Hunger),
            Comparison::Equal,
            StateValue::Constant(0)
        });
    }

    int EatGoal::DistanceTo(const PersonalState& personalState, const WorldState&)
    {
        if (!personalState.Has(PersonalKey::Hunger))
            return 1;

        for (const auto& condition : m_PersonalConditions)
        {
            if (!condition.IsSatisfied(personalState, WorldState{}))
                return 1;
        }
        return 0;
    }

    bool EatGoal::IsPersonalKeyRelated(const PersonalKey& key)
    {
        return key == PersonalKey::Hunger;
    }
} // SimWorld