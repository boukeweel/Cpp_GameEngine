//
// Created by boeken on 9/12/26.
//

#ifndef SimWorld_GOAL_H
#define SimWorld_GOAL_H
#include "States.h"

namespace SimWorld {
    class Goal {
    public:
        Goal(int priority = 0) : m_priority{priority} {};

        virtual int DistanceTo(const PersonState& state) = 0;
        virtual bool IsReached(const PersonState& state) {
            return DistanceTo(state) == 0;
        }

        [[nodiscard]] virtual const PersonState& GetDesiredState() const = 0;

        [[nodiscard]] virtual int GetPriority() const {return m_priority;}
    protected:
        int m_priority{0};
    public:
        virtual ~Goal() = default;
    };
}

#endif //SimWorld_GOAL_H
