//
// Created by boeken-work on 9/15/26.
//

#ifndef GAMEENGINE_GETFOODACTION_H
#define GAMEENGINE_GETFOODACTION_H
#include "Action.h"
#include "Event.h"

namespace SimWorld
{
    class Person;

    class GetFoodAction : public Action
    {
    public:
        GetFoodAction(Person* person);

        bool Preform() override;
        private:
        Person* m_Person;
    };
} // SimWorld

#endif //GAMEENGINE_GETFOODACTION_H
