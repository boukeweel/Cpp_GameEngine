//
// Created by boeken-work on 9/14/26.
//

#ifndef GAMEENGINE_EATACTION_H
#define GAMEENGINE_EATACTION_H
#include "../../GOAP/Action.h"
#include "Event.h"

namespace SimWorld
{
    class Person;
    class GOAPAgentComponent;

    class HungerComponent;

    class EatAction : public Action
    {
    public:
        EatAction(HungerComponent* hc,Person* agent);

        bool Preform() override;
    private:
        HungerComponent* m_HungerComp;
        Person* m_Person;
    };
} // SimWorld

#endif //GAMEENGINE_EATACTION_H
