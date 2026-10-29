//
// Created by boeken-work on 10/26/26.
//

#include "WorkJobAction.h"

#include <iostream>
#include <ostream>

#include "WorldData.h"

namespace SimWorld
{
    WorkJobAction::WorkJobAction(Person *agent) : m_Person{agent}
    {
        m_RequiredDistance = 30.0f;

        m_PersonalPreconditions.push_back({
            StateValue::Personal(PersonalKey::HasJob),
            Comparison::Equal,
            StateValue::Constant(true)
        });

        m_Effects.push_back({
            ValueSource::Personal,
            PersonalKey::WorkProgress,
            {},
            EffectOperation::Add,
            StateValue::Constant(100)
        });
        m_Effects.push_back({
            ValueSource::Personal,
            PersonalKey::Money,
            {},
            EffectOperation::Add,
            StateValue::Constant(50)
        });
    }

    ActionState WorkJobAction::Preform()
    {
        //std::cout << "Working" << std::endl;
        return ActionState::Running;
    }

    bool WorkJobAction::HasTarget() const
    {
        return m_Person->GetWorkPlace();
    }

    const GameEngine::GameObject * WorkJobAction::GetTargetObject() const
    {
        const auto* workPlace = m_Person->GetWorkPlace();
        if (workPlace == nullptr)
        {
            return nullptr;
        }

        return workPlace->GetOwner();
    }

    glm::vec3 WorkJobAction::GetTargetPosition() const
    {
        const auto* targetObject = GetTargetObject();
        if (targetObject == nullptr)
            return {};

        return targetObject->GetTransform().GetWorldPosition();
    }
} // SimWorld