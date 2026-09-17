//
// Created by boeken-work on 9/13/26.
//

#include "Planner.h"
#include <queue>
#include <map>

namespace SimWorld {
    namespace {
        using StateSignature = std::map<PersonKeys, int>;

        //make from unordered map a map
        StateSignature MakeStateSignature(const PersonState& state)
        {
            return {state.begin(), state.end()};
        }
    }

    Planner::Planner(int maxIterations) : m_MaxIterations(maxIterations) {
    }

    bool Planner::IsSatisfied(const PersonState& GoalState, const PersonState& CurrentState)
    {
        for (auto& [key, value] : GoalState) {
            auto it = CurrentState.find(key);
            if (it == CurrentState.end() || it->second != value) return false;
        }
        return true;
    }

    std::queue<Action*> Planner::Plan(const PersonState& currentState, Goal* goal,
        const std::vector<std::unique_ptr<Action>>& availableActions)
    {
        //create priority queue to always have the lowest f cost in front.
        auto cmp = [](const node* a, const node* b) { return a->fCost > b->fCost; };
        std::priority_queue<node*, std::vector<node*>, decltype(cmp)> open(cmp);

        std::vector<std::unique_ptr<node>> allocatedNodes;
        std::map<StateSignature, int> bestCosts;

        PersonState goalState = goal->GetDesiredState();

        //create the initial node
        allocatedNodes.push_back(std::make_unique<node>(
            goalState, nullptr, nullptr, 0, static_cast<int>(goalState.size())
        ));
        open.push(allocatedNodes.back().get());
        bestCosts.emplace(MakeStateSignature(goalState), 0);

        int iteration = 0;
        while (!open.empty() && iteration < m_MaxIterations) {
            iteration++;

            node* current = open.top();
            open.pop();

            const StateSignature currentSignature = MakeStateSignature(current->goal);
            const auto bestCost = bestCosts.find(currentSignature);
            if (bestCost != bestCosts.end() && current->gCost > bestCost->second)
                continue;

            //check if the goal is reached
            if (IsSatisfied(current->goal, currentState)) {
                //created a queue, and push all actions on there
                std::queue<Action*> path;
                for (node* n = current; n->parent != nullptr; n = n->parent) {
                    path.push(n->actionTaken);
                }
                return path;
            }

            //find next condition it will try to complete
            auto [key, value] = PickUnsatisfiedKey(current->goal, currentState);

            //go through every action to check
            for (auto& action : availableActions) {
                //Get the effect the action will have and check if thats something we need
                PersonState effect = action->GetEffect();
                auto it = effect.find(key);
                if (it == effect.end() || it->second != value) continue;

                //create a new goal, based on the pre conditions of the action
                PersonState nextGoal = current->goal;
                nextGoal.erase(key);
                for (auto& [pkey, pvalue] : action->GetPreConditions()) {
                    nextGoal[pkey] = pvalue;
                }

                //check if there was not a better path already.
                const int newCost = current->gCost + action->GetCost();
                const StateSignature nextSignature = MakeStateSignature(nextGoal);
                const auto bestNextCost = bestCosts.find(nextSignature);

                if (bestNextCost != bestCosts.end() &&
                    bestNextCost->second <= newCost)
                {
                    continue;
                }

                //this is now the new best cost, so push it to the priority queue
                bestCosts[nextSignature] = newCost;
                const int h = static_cast<int>(nextGoal.size());

                allocatedNodes.push_back(std::make_unique<node>(
                    nextGoal, action.get(), current, newCost, newCost + h
                ));
                open.push(allocatedNodes.back().get());
            }
        }

        return {};
    }

    std::pair<PersonKeys,int> Planner::PickUnsatisfiedKey(const PersonState &GoalState, const PersonState &CurrentState)
    {
        for (auto& [key, value] : GoalState) {
            auto it = CurrentState.find(key);
            if (it == CurrentState.end() || it->second != value) {
                return {key, value};
            }
        }
        return {};
    }
}
