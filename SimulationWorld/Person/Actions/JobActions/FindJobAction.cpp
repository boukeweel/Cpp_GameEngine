//
// Created by boeken-work on 10/29/26.
//

#include "FindJobAction.h"

#include "WorldData.h"

namespace SimWorld
{
    FindJobAction::FindJobAction(Person *agent) : m_Person(agent)
    {
        m_WorldPreconditions.push_back({
        StateValue::World(WorldKey::WorkPlaceAvailable),
            Comparison::Equal,
            StateValue::Constant(true)
        });
        m_PersonalPreconditions.push_back({
            StateValue::Personal(PersonalKey::HasJob),
            Comparison::Equal,
            StateValue::Constant(false)
        });

        m_Effects.push_back({
            ValueSource::Personal,
            PersonalKey::HasJob,
            {},
            EffectOperation::Set,
            StateValue::Constant(true)
        });
    }

    ActionState FindJobAction::Preform()
    {
        WorkPlace* workplace{WorldData::GetInstance().GetWorkPlace()};
        if (workplace == nullptr)
        {
            return ActionState::Failed;
        }

        m_Person->SetWorkPlace(workplace);
        return ActionState::Completed;
    }
} // SimWorld