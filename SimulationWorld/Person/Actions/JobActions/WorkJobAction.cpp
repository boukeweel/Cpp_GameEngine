//
// Created by boeken-work on 10/26/26.
//

#include "WorkJobAction.h"

#include <iostream>
#include <ostream>

namespace SimWorld
{
    WorkJobAction::WorkJobAction(Person *agent) : m_Person{agent}
    {
        m_PersonalPreconditions.push_back({
            StateValue::Personal(PersonalKey::HasJob),
            Comparison::Equal,
            StateValue::Constant(1)
        });

        m_Effects.push_back({
            ValueSource::Personal,
            PersonalKey::WorkProgress,
            {},
            EffectOperation::Add,
            StateValue::Constant(100)
            });
    }

    ActionState WorkJobAction::Preform()
    {
        std::cout << "Working" << std::endl;
        return ActionState::Running;
    }
} // SimWorld