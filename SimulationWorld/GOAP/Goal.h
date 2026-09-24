//
// Created by boeken on 9/12/26.
//

#ifndef SimWorld_GOAL_H
#define SimWorld_GOAL_H
#include "PersonalState.h"
#include "WorldState.h"

namespace SimWorld {
    class Goal {
    public:
        Goal(int priority = 0) : m_priority{priority} {};

        virtual int DistanceTo(const PersonalState& personalState, const WorldState& worldState) = 0;
        virtual bool IsReached(const PersonalState& personalState, const WorldState& worldState) {
            return DistanceTo(personalState, worldState) == 0;
        }

        virtual bool IsPersonalKeyRelated(const PersonalKey& key) = 0;

        [[nodiscard]] virtual const PersonalState& GetDesiredPersonalState() const = 0;
        [[nodiscard]] virtual const WorldState& GetDesiredWorldState() const = 0;

        [[nodiscard]] virtual int GetPriority() const {return m_priority;}
    protected:
        int m_priority{0};
    public:
        virtual ~Goal() = default;
    };
}

#endif //SimWorld_GOAL_H
