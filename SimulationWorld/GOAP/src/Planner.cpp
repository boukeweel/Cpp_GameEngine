//
// Created by boeken-work on 9/13/26.
//

#include "Planner.h"

#include <queue>

namespace SimWorld {
    Planner::Planner(int maxIterations) : m_MaxIterations(maxIterations) {
    }

    std::vector<Action *> Planner::plan(const PersonState &currentState, Goal *goal, const std::vector<Action *> &availableActions) {
        auto cmp = [](const node *a, const node *b) {return a->fCost > b->fCost; };
        std::priority_queue<node*, std::vector<node*>, decltype(cmp)> open(cmp);

        PersonState goalState = goal->GetDesiredState();
        node* root = new node{goalState,nullptr,nullptr,0,static_cast<int>(goalState.size())};
        open.push(root);

        int iteration = 0;
        while (!open.empty() && iteration < m_MaxIterations) {
            iteration++;

            node* current = open.top();
            open.pop();
            if (IsSatisfied(current->goal, currentState)) {
                std::vector<Action*> path;
                for (node* n = current; n->parent != nullptr; n = n->parent) {
                    path.push_back(n->actionTaken);
                }
                return path;
            }

            auto [key, value] = PickUnsatisfiedKey(current->goal, currentState);

            for (Action* action : availableActions) {
                PersonState effect = action->GetEffect();
                auto it = effect.find(key);
                if (it == effect.end() || it->second != value) continue;

                PersonState nextGoal = current->goal;
                nextGoal.erase(key);
                for (auto& [pkey, pvalue] : action->GetPreConditions()) {
                    nextGoal[pkey] = pvalue;
                }

                const int newCost = current->gCost + action->GetCost();
                const int h = static_cast<int>(nextGoal.size());
                open.push(new node{nextGoal,action,current,newCost, newCost + h});
            }
        }

        return {};
    }

    bool Planner::IsSatisfied(const PersonState& GoalState, const PersonState& CurrentState)
    {
        for (auto& [key, value] : GoalState) {
            auto it = CurrentState.find(key);
            if (it == CurrentState.end() || it->second != value) return false;
        }
        return true;
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
