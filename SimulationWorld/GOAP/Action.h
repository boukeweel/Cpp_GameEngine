//
// Created by boeken on 9/12/26.
//

#ifndef SimWorld_ACTION_H
#define SimWorld_ACTION_H
#include <string>
#include <vector>

#include "Event.h"
#include "Conditions.h"
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

        [[nodiscard]] int GetCost() const {return m_Cost;}
        [[nodiscard]] const std::string& GetName() const { return m_Name; }
        
        virtual bool IsInRange() const {return true;}
    protected:
        int m_Cost{0};

        std::string m_Name{""};
        GameEngine::Event<PersonalKey,int>* m_ChangeStateEvent{nullptr};

        std::vector<Condition> m_PersonalPreconditions;
        std::vector<Condition> m_WorldPreconditions;
        std::vector<Effect> m_Effects;
    public:
        virtual ~Action() = default;
    };
}

#endif //SimWorld_ACTION_H
