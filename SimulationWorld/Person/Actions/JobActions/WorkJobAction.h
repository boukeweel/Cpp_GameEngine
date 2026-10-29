//
// Created by boeken-work on 10/26/26.
//

#ifndef GAMEENGINE_WORKJOBACTION_H
#define GAMEENGINE_WORKJOBACTION_H

#include "Action.h"

namespace SimWorld
{
    class Person;

    class WorkJobAction : public Action
    {
    public:
        WorkJobAction(Person* agent);

        ActionState Preform() override;

        bool HasTarget() const override;
        const GameEngine::GameObject* GetTargetObject() const override;
        glm::vec3 GetTargetPosition() const override;
    private:
        Person* m_Person;

    };
} // SimWorld

#endif //GAMEENGINE_WORKJOBACTION_H
