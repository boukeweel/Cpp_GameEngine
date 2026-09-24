//
// Created by boeken on 9/12/26.
//

#ifndef SimWorld_ACTION_H
#define SimWorld_ACTION_H
#include <string>

#include "Event.h"
#include "PersonalState.h"
#include "WorldState.h"
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
        [[nodiscard]] virtual const PersonalState &GetPersonalPreconditions() const { return m_PersonalPreconditions; }
        ///give the state back with the states changed by this effect, needed for the planner
        [[nodiscard]] virtual const PersonalState &GetPersonalEffects() const { return m_PersonalEffects; }
        [[nodiscard]] virtual const WorldState &GetWorldPreconditions() const { return m_WorldPreconditions; }
        [[nodiscard]] virtual const WorldState &GetWorldEffects() const { return m_WorldEffects; }



        virtual ActionState Preform() = 0;

        [[nodiscard]] int GetCost() const {return m_Cost;}
        [[nodiscard]] const std::string& GetName() const { return m_Name; }
        
        virtual bool IsInRange() const {return true;}
    protected:
        int m_Cost{0};

        std::string m_Name{""};
        GameEngine::Event<PersonalKey,int>* m_ChangeStateEvent{nullptr};

        PersonalState m_PersonalPreconditions;
        PersonalState m_PersonalEffects;
        WorldState m_WorldPreconditions;
        WorldState m_WorldEffects;
    public:
        virtual ~Action() = default;
    };
}

#endif //SimWorld_ACTION_H
