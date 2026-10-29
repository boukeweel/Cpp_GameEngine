//
// Created by boeken-work on 10/29/26.
//

#ifndef GAMEENGINE_FINDJOBACTION_H
#define GAMEENGINE_FINDJOBACTION_H
#include "Action.h"

namespace SimWorld
{
    class Person;

    class FindJobAction : public Action
    {
    public:
        FindJobAction(Person* agent);

        ActionState Preform() override;
    private:
        Person* m_Person;
    };
} // SimWorld

#endif //GAMEENGINE_FINDJOBACTION_H
