//
// Created by boeken-work on 9/15/26.
//

#ifndef GAMEENGINE_GETFOODACTION_H
#define GAMEENGINE_GETFOODACTION_H
#include "../../GOAP/Action.h"
#include "Event.h"

namespace SimWorld
{
    class GOAPAgentComponent;

    class BuyFoodAction : public Action
    {
    public:
        BuyFoodAction(GOAPAgentComponent* agent);

        bool Preform() override;
        private:
        GOAPAgentComponent* m_GoapAgent;
    };
} // SimWorld

#endif //GAMEENGINE_GETFOODACTION_H
