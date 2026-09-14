//
// Created by boeken-work on 9/14/26.
//

#ifndef GAMEENGINE_EATACTION_H
#define GAMEENGINE_EATACTION_H
#include "Action.h"

namespace SimWorld
{
    class EatAction : public Action
    {
    public:
        EatAction();

        bool Preform(PersonState &state) override;
    };
} // SimWorld

#endif //GAMEENGINE_EATACTION_H
