//
// Created by boeken-work on 9/14/26.
//

#ifndef GAMEENGINE_EATGOAL_H
#define GAMEENGINE_EATGOAL_H
#include "Goal.h"

namespace SimWorld {
    class EatGoal : public Goal
    {
    public:
        EatGoal();

        int DistanceTo(const PersonState &state) override;
        const PersonState &GetDesiredState() const override {return m_DesiredState;}

        bool IsKeyRelated(const PersonKeys &key) override;

        void ChangePriority(int newPriority){m_priority = newPriority;}

    private:
        PersonState m_DesiredState;
    };
} // SimWorld

#endif //GAMEENGINE_EATGOAL_H
