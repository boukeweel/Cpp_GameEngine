//
// Created by boeken on 9/12/26.
//

#ifndef SimWorld_ACTION_H
#define SimWorld_ACTION_H

namespace SimWorld {
    class Action
    {
    public:
        virtual bool CanPreform() = 0;
        virtual bool PlanEffects() = 0;
        virtual bool Preform() = 0;

        virtual ~Action() = default;
    protected:
        int Cost{0};
    };
}

#endif //SimWorld_ACTION_H
