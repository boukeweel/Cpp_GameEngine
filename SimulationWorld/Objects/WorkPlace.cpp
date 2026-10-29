//
// Created by boeken-work on 10/29/26.
//

#include "WorkPlace.h"

#include "WorldData.h"

namespace SimWorld
{
    WorkPlace::WorkPlace(GameEngine::GameObject *owner) : Component(owner)
    {
        WorldData::GetInstance().AddWorkPlace(this);
    }
} // SimWorld