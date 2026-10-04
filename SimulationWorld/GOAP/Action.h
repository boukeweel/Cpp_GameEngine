//
// Created by boeken on 9/12/26.
//

#ifndef SimWorld_ACTION_H
#define SimWorld_ACTION_H
#include <string>
#include <vector>

#include <glm/glm.hpp>

#include "Event.h"
#include "Conditions.h"
#include "GameObject.h"
#include "Transform.h"
#include "States.h"

namespace SimWorld {

    enum class ActionState
    {
        Completed,
        Running,
        Failed,
        Aborted,
    };

    class Action
    {
    public:
        [[nodiscard]] const std::vector<Condition>& GetPersonalPreconditions() const { return m_PersonalPreconditions; }
        [[nodiscard]] const std::vector<Condition>& GetWorldPreconditions() const { return m_WorldPreconditions; }
        [[nodiscard]] const std::vector<Effect>& GetEffects() const { return m_Effects; }

        virtual ActionState Preform() = 0;

        [[nodiscard]] int GetCost() const { return m_Cost; }
        [[nodiscard]] const std::string& GetName() const { return m_Name; }

        virtual bool HasTarget() const { return m_TargetObject != nullptr; }
        virtual void SetTargetObject(GameEngine::GameObject* targetObject) { m_TargetObject = targetObject; }
        virtual const GameEngine::GameObject* GetTargetObject() const { return m_TargetObject; }
        virtual void SetRequiredDistance(float requiredDistance) { m_RequiredDistance = requiredDistance; }
        virtual float GetRequiredDistance() const { return m_RequiredDistance; }
        virtual glm::vec3 GetTargetPosition() const
        {
            if (m_TargetObject == nullptr)
                return {};

            return m_TargetObject->GetTransform().GetWorldPosition();
        }

        virtual bool IsInRange() const
        {
            if (!HasTarget() || m_AgentOwner == nullptr)
                return true;

            const glm::vec3 direction = GetTargetPosition() - m_AgentOwner->GetTransform().GetWorldPosition();
            return glm::length(direction) <= GetRequiredDistance();
        }

        virtual void SetAgentOwner(GameEngine::GameObject* owner) { m_AgentOwner = owner; }
        [[nodiscard]] virtual GameEngine::GameObject* GetAgentOwner() const { return m_AgentOwner; }

    protected:
        int m_Cost{0};
        float m_RequiredDistance{0.0f};

        std::string m_Name{""};
        GameEngine::Event<PersonalKey,int>* m_ChangeStateEvent{nullptr};

        std::vector<Condition> m_PersonalPreconditions;
        std::vector<Condition> m_WorldPreconditions;
        std::vector<Effect> m_Effects;
        GameEngine::GameObject* m_TargetObject{nullptr};
        GameEngine::GameObject* m_AgentOwner{nullptr};
    public:
        virtual ~Action() = default;
    };
}

#endif //SimWorld_ACTION_H
