//
// Created by boeken-work on 10/27/26.
//

#include "WorkGoal.h"

namespace SimWorld
{
    WorkGoal::WorkGoal() : Goal(1)
    {
        m_PersonalConditions.push_back({
            StateValue::Personal(PersonalKey::WorkProgress),
            Comparison::GreaterOrEqual,
            StateValue::Constant(100) // Magic number bad
        });
    }

    int WorkGoal::DistanceTo(const PersonalState &personalState, const WorldState &worldState)
    {
        if (!personalState.Has(PersonalKey::WorkProgress))
            return 1;

        for (const auto& condition : m_PersonalConditions)
        {
            if (!condition.IsSatisfied(personalState, worldState))
                return 1;
        }
        return 0;
    }

    bool WorkGoal::IsPersonalKeyRelated(const PersonalKey &key)
    {
        return key == PersonalKey::WorkProgress;
    }
} // SimWorld