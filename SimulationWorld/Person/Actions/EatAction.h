//
// Created by boeken-work on 9/14/26.
//

#ifndef GAMEENGINE_EATACTION_H
#define GAMEENGINE_EATACTION_H
#include "Action.h"
#include "Event.h"

namespace SimWorld
{
    class HungerComponent;

    class EatAction : public Action
    {
    public:
        EatAction(HungerComponent* hc,GameEngine::Event<PersonKeys,int>* changeStateEvent);

        bool Preform() override;
    private:
        HungerComponent* m_HungerComp;
    };
} // SimWorld

#endif //GAMEENGINE_EATACTION_H
