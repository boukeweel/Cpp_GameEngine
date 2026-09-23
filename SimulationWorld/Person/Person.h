//
// Created by boeken-work on 9/13/26.
//

#ifndef GAMEENGINE_PERSON_H
#define GAMEENGINE_PERSON_H
#include <memory>
#include <queue>
#include <vector>
#include "Component.h"
#include "Event.h"
#include "../GOAP/States.h"

namespace SimWorld {
    class GOAPAgentComponent;
    class Inventory;
    class Wallet;
    class Planner;
    class Goal;
    class Action;

    //todo I should prop make this a GOAP agent and Person class.
    //split them up, but for now I am going to keep it simple till I got enough working that I deem it needed
    class Person : public GameEngine::Component {
    public:
        Person(GameEngine::GameObject* owner);
        void Begin() override;

        void FixedUpdate() override;

        Wallet& GetWallet() const {return *m_Wallet;}
        Inventory& GetInventory() const {return *m_Inventory;}
        GOAPAgentComponent* GetGOAPAgentComponent() const {return m_AgentComponent;}
    private:
        void InitActions();
        void InitGoals();
        void InitStates();

        std::unique_ptr<Wallet> m_Wallet{};
        std::unique_ptr<Inventory> m_Inventory{};

        GOAPAgentComponent* m_AgentComponent{};
    public:
        ~Person() override;
    };

} // SimWorld

#endif //GAMEENGINE_PERSON_H
