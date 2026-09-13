//
// Created by boeken on 9/12/26.
//

#ifndef SimWorld_GOAL_H
#define SimWorld_GOAL_H
#include "States.h"

namespace SimWorld {
    class Goal {
    public:
        virtual int DistanceTo(const PersonState& state) = 0;
        virtual bool IsReached(const PersonState& state) {
            return DistanceTo(state) == 0;
        }

        virtual const PersonState& GetDesiredState() const = 0;

        [[nodiscard]] int GetPriority() const {return m_priority;}
    protected:
        int m_priority{0};
    public:
        virtual ~Goal() = default;
    };
}

#endif //SimWorld_GOAL_H
