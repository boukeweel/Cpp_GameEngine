//
// Created by boeken-work on 9/13/26.
//

#include "Person.h"

#include "BuyFoodAction.h"
#include "EatAction.h"
#include "EatGoal.h"
#include "GameObject.h"
#include "HungerComponent.h"
#include "Inventory.h"
#include "Wallet.h"
#include "GOAPAgentComponent.h"

namespace SimWorld {
    Person::Person(GameEngine::GameObject *owner) : Component(owner)
    {

        m_Wallet = std::make_unique<Wallet>(this,100);
        m_Inventory = std::make_unique<Inventory>(this);
    }

    void Person::Begin()
    {
        m_AgentComponent = m_Owner->GetComponent<GOAPAgentComponent>();
        if (m_AgentComponent != nullptr)
        {
            InitActions();
            InitGoals();
            InitStates();
        }
    }
    void Person::InitActions()
    {
        m_AgentComponent->AddAction(std::make_unique<BuyFoodAction>(this));
        HungerComponent* hunger = m_Owner->GetComponent<HungerComponent>();
        if (hunger != nullptr)
            m_AgentComponent->AddAction(std::make_unique<EatAction>(hunger,this));
    }

    void Person::InitGoals()
    {
        m_AgentComponent->AddGoal(std::make_unique<EatGoal>());
    }

    void Person::InitStates()
    {
        m_AgentComponent->AddState(PersonalKey::FoodQuantity, m_Inventory->GetQuantity(ItemType::Food));
        m_AgentComponent->AddState(PersonalKey::Money, m_Wallet->GetBalance());
        m_AgentComponent->AddState(PersonalKey::Hunger, 0);
    }

    void Person::FixedUpdate()
    {
    }



    Person::~Person() = default;
} // SimWorld