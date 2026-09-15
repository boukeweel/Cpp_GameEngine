//
// Created by boeken-work on 9/15/26.
//

#ifndef GAMEENGINE_GETFOODACTION_H
#define GAMEENGINE_GETFOODACTION_H
#include "Action.h"

namespace SimWorld
{
    class GetFoodAction : public Action
    {
    public:
        GetFoodAction();

        bool Preform(PersonState& state) override;
    };
} // SimWorld

#endif //GAMEENGINE_GETFOODACTION_H
