//
// Created by boeken-work on 9/15/26.
//

#include "BuyFoodAction.h"

#include <iostream>
#include <ostream>

#include "GOAPAgentComponent.h"
#include "Person.h"
#include "WorldData.h"

namespace SimWorld
{
    BuyFoodAction::BuyFoodAction(Person* agent) : m_Person{agent}
    {
        m_PersonalPreconditions.push_back({
            StateValue::Personal(PersonalKey::Money),
            Comparison::GreaterOrEqual,
            StateValue::World(WorldKey::FoodPrice)
        });
        m_WorldPreconditions.push_back({
            StateValue::World(WorldKey::StoreAvailable),
            Comparison::GreaterOrEqual,
            StateValue::Constant(1)
        });
        m_WorldPreconditions.push_back({
            StateValue::World(WorldKey::FoodAvailable),
            Comparison::GreaterOrEqual,
            StateValue::Constant(1)
        });
        m_Effects.push_back({
            ValueSource::Personal,
            PersonalKey::FoodQuantity,
            {},
            EffectOperation::Add,
            StateValue::Constant(1)
        });
        m_Effects.push_back({
            ValueSource::Personal,
            PersonalKey::Money,
            {},
            EffectOperation::Subtract,
            StateValue::World(WorldKey::FoodPrice)
        });
        m_Name = "BuyFoodAction";
    }

    ActionState BuyFoodAction::Preform()
    {
        if (m_Person == nullptr)
            return ActionState::Aborted;

        //todo I want the agent to hold there favorite food store, so I dont have to get it every time from the worldData
        auto store = WorldData::GetInstance().GetFoodStore();
        if (store == nullptr) return ActionState::Aborted;

        if (store->GetPrice() > m_Person->GetWallet().GetBalance())
            return ActionState::Failed;

        if (store->Buy(m_Person->GetWallet(),m_Person->GetInventory(),1))
        {
            m_Person->GetGOAPAgentComponent()->SetState(
                PersonalKey::Money,
                m_Person->GetWallet().GetBalance());
            std::cout << "Got food" << std::endl;
            return ActionState::Completed;
        }

        return ActionState::Running;
    }
} // SimWorld