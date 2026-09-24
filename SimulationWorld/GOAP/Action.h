//
// Created by boeken on 9/12/26.
//

#ifndef SimWorld_ACTION_H
#define SimWorld_ACTION_H
#include <string>

#include "Event.h"
#include "States.h"

namespace SimWorld {

    enum class ActionState
    {
        Completed,
        Running,
        Failed,
        Aborted,
    };

    class Action
    {
    public:
        ///Get the conditions that needs to be met for this action to be able to preform
        [[nodiscard]] virtual const PersonState &GetPreConditions() const { return m_PreConditions; }
        ///give the state back with the states changed by this effect, needed for the planner
        [[nodiscard]] virtual const PersonState &GetEffect() const { return m_Effects; }

        virtual ActionState Preform() = 0;

        [[nodiscard]] int GetCost() const {return m_Cost;}
        [[nodiscard]] const std::string& GetName() const { return m_Name; }
        
        virtual bool IsInRange() const {return true;}
    protected:
        int m_Cost{0};

        std::string m_Name{""};
        PersonState m_PreConditions;
        PersonState m_Effects;

        GameEngine::Event<PersonKeys,int>* m_ChangeStateEvent{nullptr};
    public:
        virtual ~Action() = default;
    };
}

#endif //SimWorld_ACTION_H
