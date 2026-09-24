//
// Created by boeken-work on 9/14/26.
//

#include "EatGoal.h"

namespace SimWorld {
    EatGoal::EatGoal() : Goal(10)
    {
        m_DesiredState.Set(PersonalKey::Hunger, 0);
    }

    int EatGoal::DistanceTo(const PersonalState& personalState, const WorldState&)
    {
        if (!personalState.Has(PersonalKey::Hunger))
            return 1;

        if (personalState.Get(PersonalKey::Hunger) == m_DesiredState.Get(PersonalKey::Hunger))
            return 0;

        return 1;
    }

    bool EatGoal::IsPersonalKeyRelated(const PersonalKey& key)
    {
        return m_DesiredState.Has(key);
    }
} // SimWorld