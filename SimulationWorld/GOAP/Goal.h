//
// Created by boeken on 9/12/26.
//

#ifndef SimWorld_GOAL_H
#define SimWorld_GOAL_H
#include <vector>

#include "Conditions.h"
#include "Event.h"

namespace SimWorld {

    using PriorityChangedEvent = GameEngine::Event<int, int>;

    class Goal {
    public:
        Goal(int priority = 0) : m_priority{priority} {};

        //todo put in .cpp
        void ChangePriority(int newPriority)
        {
            if (m_priority == newPriority)
                return;

            const int oldPriority = m_priority;
            m_priority = newPriority;
            m_PriorityChangedEvent.Invoke(oldPriority, newPriority);
        }
        [[nodiscard]] virtual int GetPriority() const {return m_priority;}
        PriorityChangedEvent& GetPriorityChangedEvent() { return m_PriorityChangedEvent; }

        virtual int DistanceTo(const PersonalState& personalState, const WorldState& worldState) = 0;
        virtual bool IsReached(const PersonalState& personalState, const WorldState& worldState) {
            return DistanceTo(personalState, worldState) == 0;
        }

        virtual bool IsPersonalKeyRelated(const PersonalKey& key) = 0;

        virtual const std::vector<Condition>& GetWorldConditions() const {return m_WorldConditions;}
        virtual const std::vector<Condition>& GetPersonalConditions() const {return m_PersonalConditions;}
    protected:
        std::vector<Condition> m_PersonalConditions;
        std::vector<Condition> m_WorldConditions;

    private:
        int m_priority{0};
        PriorityChangedEvent m_PriorityChangedEvent;

    public:
        virtual ~Goal() = default;
    };
}

#endif //SimWorld_GOAL_H
