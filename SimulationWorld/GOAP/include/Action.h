//
// Created by boeken on 9/12/26.
//

#ifndef SimWorld_ACTION_H
#define SimWorld_ACTION_H
#include "States.h"

namespace SimWorld {
    class Action
    {
    public:
        ///Get the conditions that needs to be met for this action to be able to preform
        [[nodiscard]] virtual const PersonState& GetPreConditions() const = 0;
        ///give the state back with the states changed by this effect, needed for the planner
        [[nodiscard]] virtual const PersonState& GetEffect() const = 0;

        virtual bool Preform(PersonState& state) = 0;

        [[nodiscard]] int GetCost() const {return m_Cost;}


    protected:
        int m_Cost{0};
    public:
        virtual ~Action() = default;
    };
}

#endif //SimWorld_ACTION_H
