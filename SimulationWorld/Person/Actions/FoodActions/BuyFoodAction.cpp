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
        m_RequiredDistance = 30.0f;

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

    bool BuyFoodAction::HasTarget() const
    {
        return WorldData::GetInstance().GetFoodStore() != nullptr;
    }

    const GameEngine::GameObject* BuyFoodAction::GetTargetObject() const
    {
        const auto* store = WorldData::GetInstance().GetFoodStore();
        if (store == nullptr)
            return nullptr;

        return store->GetOwner();
    }

    glm::vec3 BuyFoodAction::GetTargetPosition() const
    {
        const auto* targetObject = GetTargetObject();
        if (targetObject == nullptr)
            return {};

        return targetObject->GetTransform().GetWorldPosition();
    }

    float BuyFoodAction::GetRequiredDistance() const
    {
        return m_RequiredDistance;
    }

    ActionState BuyFoodAction::Preform()
    {
        if (m_Person == nullptr)
            return ActionState::Aborted;

        //todo should hold its favorite store, when there are more stores then just one
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