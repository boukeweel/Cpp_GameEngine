//
// Created by boeken-work on 9/13/26.
//

#include "Planner.h"
#include <queue>
#include <map>

namespace SimWorld {
    namespace {
        using StateSignature = std::map<PersonalKey, int>;

        //make from unordered map a map
        StateSignature MakeStateSignature(const PersonalState& state)
        {
            return {state.Values().begin(), state.Values().end()};
        }
    }

    Planner::Planner(int maxIterations) : m_MaxIterations(maxIterations) {
    }

    bool Planner::IsSatisfied(const PersonalState& requiredState, const PersonalState& currentState)
    {
        for (const auto& [key, value] : requiredState.Values()) {
            if (!currentState.Has(key) || currentState.Get(key) != value) return false;
        }
        return true;
    }

    bool Planner::IsWorldSatisfied(const WorldState& requiredState, const WorldState& currentState)
    {
        for (const auto& [key, value] : requiredState.Values()) {
            if (!currentState.Has(key) || currentState.Get(key) != value) return false;
        }
        return true;
    }

    bool Planner::IsKeySatisfied(PersonalKey key, int value, const PersonalState &currentState)
    {
        return currentState.Has(key) && currentState.Get(key) == value;
    }

    std::queue<Action*> Planner::Plan(const PersonalState& personalState, const WorldState& worldState, Goal* goal,
                                      const std::vector<std::unique_ptr<Action>>& availableActions)
    {
        //create priority queue to always have the lowest f cost in front.
        auto cmp = [](const node* a, const node* b) { return a->fCost > b->fCost; };
        std::priority_queue<node*, std::vector<node*>, decltype(cmp)> open(cmp);

        std::vector<std::unique_ptr<node>> allocatedNodes;
        std::map<StateSignature, int> bestCosts;

        PersonalState goalState = goal->GetDesiredPersonalState();
        const WorldState& requiredWorldState = goal->GetDesiredWorldState();

        //create the initial node
        allocatedNodes.push_back(std::make_unique<node>(
            goalState, requiredWorldState, nullptr, nullptr, 0, static_cast<int>(goalState.Values().size())
        ));
        open.push(allocatedNodes.back().get());
        bestCosts.emplace(MakeStateSignature(goalState), 0);

        int iteration = 0;
        while (!open.empty() && iteration < m_MaxIterations) {
            iteration++;

            node* current = open.top();
            open.pop();

            const StateSignature currentSignature = MakeStateSignature(current->requiredPersonalState);
            const auto bestCost = bestCosts.find(currentSignature);
            if (bestCost != bestCosts.end() && current->gCost > bestCost->second)
                continue;

            //check if the goal is reached
            if (IsSatisfied(current->requiredPersonalState, personalState) &&
                IsWorldSatisfied(current->requiredWorldState, worldState)) {
                //created a queue, and push all actions on there
                std::queue<Action*> path;
                for (node* n = current; n->parent != nullptr; n = n->parent) {
                    path.push(n->actionTaken);
                }
                return path;
            }

            //find next condition it will try to complete
            for (const auto& [key, value] : current->requiredPersonalState.Values())
            {
                if (IsKeySatisfied(key, value, personalState)) continue; // skip already-satisfied keys

                for (auto& action : availableActions) {
                    if (!IsWorldSatisfied(action->GetWorldPreconditions(), worldState))
                    {
                        continue;
                    }

                    const auto& effect = action->GetPersonalEffects();
                    if (!effect.Has(key) || effect.Get(key) != value) continue;

                    // conflict check: does this action break any OTHER still-required key?
                    bool conflicts = false;
                    for (const auto& [gKey, gValue] : current->requiredPersonalState.Values()) {
                        if (gKey == key) continue;
                        if (effect.Has(gKey) && effect.Get(gKey) != gValue) { conflicts = true; break; }
                    }
                    if (conflicts) continue;

                    PersonalState nextGoal = current->requiredPersonalState;
                    for (const auto& [eKey, eValue] : effect.Values()) {
                        if (nextGoal.Has(eKey) && nextGoal.Get(eKey) == eValue)
                        {
                            nextGoal.Erase(eKey);
                        }
                    }
                    for (const auto& [pkey, pvalue] : action->GetPersonalPreconditions().Values()) {
                        nextGoal.Set(pkey, pvalue);
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
                    const int h = static_cast<int>(nextGoal.Values().size());

                    allocatedNodes.push_back(std::make_unique<node>(
                        nextGoal, current->requiredWorldState, action.get(), current, newCost, newCost + h
                    ));
                    open.push(allocatedNodes.back().get());
                }
            }
        }

        return {};
    }

    Goal* Planner::GetNewGoal(const PersonalState& personalState, const WorldState& worldState,
                              const std::vector<std::unique_ptr<Goal>>& goals)
    {
        Goal* bestGoal = nullptr;
        int bestPriority = -1; // anything <= -1 is invalid, so this is a safe starting floor

        for (auto& goal : goals) {
            if (goal->GetPriority() <= -1) continue;      // invalid goal
            if (goal->IsReached(personalState, worldState)) continue;   // already satisfied, skip

            if (goal->GetPriority() > bestPriority) {
                bestPriority = goal->GetPriority();
                bestGoal = goal.get();
            }
        }

        //return nullptr if there is no valid goal
        return bestGoal;
    }
}
