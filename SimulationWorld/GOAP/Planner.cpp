#include "Planner.h"

#include <map>
#include <queue>
#include <tuple>

namespace SimWorld
{
    namespace
    {
        using PersonalSignature = std::map<PersonalKey, int>;
        using WorldSignature = std::map<WorldKey, int>;

        struct StateSignature
        {
            PersonalSignature personal;
            WorldSignature world;

            bool operator<(const StateSignature& other) const
            {
                return std::tie(personal, world) < std::tie(other.personal, other.world);
            }
        };

        PersonalSignature MakePersonalSignature(const PersonalState& state)
        {
            return {state.Values().begin(), state.Values().end()};
        }

        WorldSignature MakeWorldSignature(const WorldState& state)
        {
            return {state.Values().begin(), state.Values().end()};
        }

        StateSignature MakeStateSignature(const PersonalState& personalState,
                                          const WorldState& worldState)
        {
            return {
                MakePersonalSignature(personalState),
                MakeWorldSignature(worldState)
            };
        }
    }

    Planner::Planner(int maxIterations)
        : m_MaxIterations(maxIterations)
    {
    }

    bool Planner::AreSatisfied(const std::vector<Condition>& conditions,
                               const PersonalState& personalState,
                               const WorldState& worldState) const
    {
        for (const auto& condition : conditions)
        {
            if (!condition.IsSatisfied(personalState, worldState))
            {
                return false;
            }
        }
        return true;
    }

    int Planner::CountUnsatisfied(const Goal& goal,
                                  const PersonalState& personalState,
                                  const WorldState& worldState) const
    {
        int unsatisfied = 0;
        for (const auto& condition : goal.GetPersonalConditions())
        {
            if (!condition.IsSatisfied(personalState, worldState))
            {
                ++unsatisfied;
            }
        }
        for (const auto& condition : goal.GetWorldConditions())
        {
            if (!condition.IsSatisfied(personalState, worldState))
            {
                ++unsatisfied;
            }
        }
        return unsatisfied;
    }

    std::queue<Action*> Planner::Plan(
        const PersonalState& personalState,
        const WorldState& worldState,
        Goal* goal,
        const std::vector<std::unique_ptr<Action>>& availableActions)
    {
        if (goal == nullptr)
        {
            return {};
        }

        auto compare = [](const node* left, const node* right)
        {
            return left->fCost > right->fCost;
        };
        std::priority_queue<node*, std::vector<node*>, decltype(compare)> open(compare);
        std::vector<std::unique_ptr<node>> allocatedNodes;
        std::map<StateSignature, int> bestCosts;

        allocatedNodes.push_back(std::make_unique<node>(
            personalState,
            worldState,
            nullptr,
            nullptr,
            0,
            CountUnsatisfied(*goal, personalState, worldState)));
        open.push(allocatedNodes.back().get());
        bestCosts.emplace(MakeStateSignature(personalState, worldState), 0);

        int iteration = 0;
        while (!open.empty() && iteration < m_MaxIterations)
        {
            ++iteration;
            node* current = open.top();
            open.pop();

            const auto signature = MakeStateSignature(
                current->personalState,
                current->worldState);
            const auto bestCost = bestCosts.find(signature);
            if (bestCost != bestCosts.end() && current->gCost > bestCost->second)
            {
                continue;
            }

            if (goal->IsReached(current->personalState, current->worldState))
            {
                std::vector<Action*> reversedPath;
                for (node* pathNode = current; pathNode->parent != nullptr;
                     pathNode = pathNode->parent)
                {
                    reversedPath.push_back(pathNode->actionTaken);
                }

                std::queue<Action*> path;
                for (auto it = reversedPath.rbegin(); it != reversedPath.rend(); ++it)
                {
                    path.push(*it);
                }
                return path;
            }

            for (const auto& action : availableActions)
            {
                if (!AreSatisfied(action->GetPersonalPreconditions(),
                                  current->personalState,
                                  current->worldState) ||
                    !AreSatisfied(action->GetWorldPreconditions(),
                                  current->personalState,
                                  current->worldState))
                {
                    continue;
                }

                PersonalState nextPersonalState = current->personalState;
                WorldState nextWorldState = current->worldState;
                for (const auto& effect : action->GetEffects())
                {
                    effect.Apply(nextPersonalState, nextWorldState);
                }

                const int newCost = current->gCost + action->GetCost();
                const auto nextSignature = MakeStateSignature(
                    nextPersonalState,
                    nextWorldState);
                const auto bestNextCost = bestCosts.find(nextSignature);
                if (bestNextCost != bestCosts.end() &&
                    bestNextCost->second <= newCost)
                {
                    continue;
                }

                bestCosts[nextSignature] = newCost;
                const int heuristic = CountUnsatisfied(
                    *goal,
                    nextPersonalState,
                    nextWorldState);

                allocatedNodes.push_back(std::make_unique<node>(
                    nextPersonalState,
                    nextWorldState,
                    action.get(),
                    current,
                    newCost,
                    newCost + heuristic));
                open.push(allocatedNodes.back().get());
            }
        }

        return {};
    }

    Goal* Planner::GetNewGoal(
        const PersonalState& personalState,
        const WorldState& worldState,
        const std::vector<std::unique_ptr<Goal>>& goals)
    {
        Goal* bestGoal = nullptr;
        int bestPriority = -1;

        for (const auto& goal : goals)
        {
            if (goal->GetPriority() <= -1 ||
                goal->IsReached(personalState, worldState))
            {
                continue;
            }

            if (goal->GetPriority() > bestPriority)
            {
                bestPriority = goal->GetPriority();
                bestGoal = goal.get();
            }
        }

        return bestGoal;
    }
}
