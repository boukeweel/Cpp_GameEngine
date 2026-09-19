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

    bool Planner::IsKeySatisfied(const PersonKeys &key, const int &value, const PersonState &currentState)
    {
        auto it = currentState.find(key);
        return it != currentState.end() && it->second == value;
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
            for (auto& [key, value] : current->goal)
            {
                if (IsKeySatisfied(key, value, currentState)) continue; // skip already-satisfied keys

                for (auto& action : availableActions) {
                    PersonState effect = action->GetEffect();
                    auto it = effect.find(key);
                    if (it == effect.end() || it->second != value) continue;

                    // conflict check: does this action break any OTHER still-required key?
                    bool conflicts = false;
                    for (auto& [gKey, gValue] : current->goal) {
                        if (gKey == key) continue;
                        auto eIt = effect.find(gKey);
                        if (eIt != effect.end() && eIt->second != gValue) { conflicts = true; break; }
                    }
                    if (conflicts) continue;

                    PersonState nextGoal = current->goal;
                    for (auto& [eKey, eValue] : effect) {
                        auto gIt = nextGoal.find(eKey);
                        if (gIt != nextGoal.end() && gIt->second == eValue) nextGoal.erase(gIt);
                    }
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
        }

        return {};
    }

    Goal* Planner::GetNewGoal(const PersonState &currentState, const std::vector<std::unique_ptr<Goal>> & goals)
    {
        Goal* bestGoal = nullptr;
        int bestPriority = -1; // anything <= -1 is invalid, so this is a safe starting floor

        for (auto& goal : goals) {
            if (goal->GetPriority() <= -1) continue;      // invalid goal
            if (goal->IsReached(currentState)) continue;   // already satisfied, skip

            if (goal->GetPriority() > bestPriority) {
                bestPriority = goal->GetPriority();
                bestGoal = goal.get();
            }
        }

        //return nullptr if there is no valid goal
        return bestGoal;
    }
}
