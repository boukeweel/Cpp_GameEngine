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
        virtual bool CanPreform(const PersonState& state) = 0;
        virtual void PlanEffects(PersonState& state) = 0;
        virtual bool Preform(PersonState& state) = 0;

        [[nodiscard]] int GetCost() const {return m_Cost;}


    protected:
        int m_Cost{0};
    public:
        virtual ~Action() = default;
    };
}

#endif //SimWorld_ACTION_H
