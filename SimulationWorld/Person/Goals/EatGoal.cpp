//
// Created by boeken-work on 9/14/26.
//

#include "EatGoal.h"

namespace SimWorld {
    EatGoal::EatGoal() : Goal(10)
    {
        m_DesiredState[PersonKeys::Hunger] = 0;
    }

    int EatGoal::DistanceTo(const PersonState &state)
    {
        const auto it = state.find(PersonKeys::Hunger);
        if (it == state.end())
            return 1;

        if (it->second == m_DesiredState.at(PersonKeys::Hunger))
            return 0;

        return 1;
    }

    bool EatGoal::IsKeyRelated(const PersonKeys &key)
    {
        return m_DesiredState.contains(key);
    }
} // SimWorld