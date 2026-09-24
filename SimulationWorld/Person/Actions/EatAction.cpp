//
// Created by boeken-work on 9/14/26.
//

#include "EatAction.h"
#include "HungerComponent.h"
#include <iostream>

#include "GOAPAgentComponent.h"
#include "Person.h"
#include "Inventory.h"

namespace SimWorld
{
    EatAction::EatAction(HungerComponent* hc,Person* agent) : m_Person{agent}, m_HungerComp{hc}
    {
        m_PersonalPreconditions.push_back({
            StateValue::Personal(PersonalKey::FoodQuantity),
            Comparison::GreaterOrEqual,
            StateValue::Constant(1)
        });
        m_Effects.push_back({
            ValueSource::Personal,
            PersonalKey::Hunger,
            {},
            EffectOperation::Set,
            StateValue::Constant(0)
        });
        m_Effects.push_back({
            ValueSource::Personal,
            PersonalKey::FoodQuantity,
            {},
            EffectOperation::Subtract,
            StateValue::Constant(1)
        });

        m_Name = "Eat Action";
    }

    ActionState EatAction::Preform()
    {
        if (m_HungerComp == nullptr || m_Person == nullptr)
            return ActionState::Aborted;

        if (m_Person->GetInventory().Remove(ItemType::Food,1))
        {
            m_HungerComp->AteFood();
            m_Person->GetGOAPAgentComponent()->SetState(PersonalKey::Hunger, 0);

            std::cout << "Eating" << std::endl;
            return ActionState::Completed;
        }

        return ActionState::Running;

    }
} // SimWorld