//
// Created by boeken-work on 9/15/26.
//

#ifndef GAMEENGINE_GETFOODACTION_H
#define GAMEENGINE_GETFOODACTION_H
#include "Action.h"

namespace SimWorld
{
    class Person;
    class GOAPAgentComponent;

    class BuyFoodAction : public Action
    {
    public:
        BuyFoodAction(Person* agent);

        bool Preform() override;
    private:
        Person* m_Person{nullptr};
    };
} // SimWorld

#endif //GAMEENGINE_GETFOODACTION_H
