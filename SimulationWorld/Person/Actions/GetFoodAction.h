//
// Created by boeken-work on 9/15/26.
//

#ifndef GAMEENGINE_GETFOODACTION_H
#define GAMEENGINE_GETFOODACTION_H
#include "Action.h"
#include "Event.h"

namespace SimWorld
{
    class GetFoodAction : public Action
    {
    public:
        GetFoodAction(GameEngine::Event<PersonKeys,int>* changeStateEvent);

        bool Preform() override;
    };
} // SimWorld

#endif //GAMEENGINE_GETFOODACTION_H
