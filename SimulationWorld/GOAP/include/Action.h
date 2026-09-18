//
// Created by boeken on 9/12/26.
//

#ifndef SimWorld_ACTION_H
#define SimWorld_ACTION_H
#include "Event.h"
#include "States.h"

namespace SimWorld {
    class Action
    {
    public:
        ///Get the conditions that needs to be met for this action to be able to preform
        [[nodiscard]] virtual const PersonState &GetPreConditions() const { return m_PreConditions; }
        ///give the state back with the states changed by this effect, needed for the planner
        [[nodiscard]] virtual const PersonState &GetEffect() const { return m_Effects; }

        virtual bool Preform() = 0;

        [[nodiscard]] int GetCost() const {return m_Cost;}


    protected:
        int m_Cost{0};

        PersonState m_PreConditions;
        PersonState m_Effects;

        GameEngine::Event<PersonKeys,int>* m_ChangeStateEvent{nullptr};
    public:
        virtual ~Action() = default;
    };
}

#endif //SimWorld_ACTION_H
