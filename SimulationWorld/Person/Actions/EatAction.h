//
// Created by boeken-work on 9/14/26.
//

#ifndef GAMEENGINE_EATACTION_H
#define GAMEENGINE_EATACTION_H
#include "../../GOAP/Action.h"
#include "Event.h"

namespace SimWorld
{
    class GOAPAgentComponent;

    class HungerComponent;

    class EatAction : public Action
    {
    public:
        EatAction(HungerComponent* hc,GOAPAgentComponent* agent);

        bool Preform() override;
    private:
        HungerComponent* m_HungerComp;
        GOAPAgentComponent* m_GoapAgent;
    };
} // SimWorld

#endif //GAMEENGINE_EATACTION_H
