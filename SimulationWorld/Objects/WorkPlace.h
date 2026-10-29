//
// Created by boeken-work on 10/29/26.
//

#ifndef GAMEENGINE_WORKPLACE_H
#define GAMEENGINE_WORKPLACE_H
#include "Component.h"

namespace SimWorld
{
    class WorkPlace : public GameEngine::Component
    {
    public:
        WorkPlace(GameEngine::GameObject* owner);
    };
} // SimWorld

#endif //GAMEENGINE_WORKPLACE_H
