//
// Created by boeken-work on 10/26/26.
//

#include "WorkJobAction.h"

namespace SimWorld
{
    WorkJobAction::WorkJobAction(Person *agent) : m_Person{agent}
    {
        m_PersonalPreconditions.push_back({
            StateValue::Personal(PersonalKey::HasJob),
            Comparison::Equal,
            StateValue::Constant(1)
        });
    }

    ActionState WorkJobAction::Preform()
    {

        return ActionState::Failed;
    }
} // SimWorld