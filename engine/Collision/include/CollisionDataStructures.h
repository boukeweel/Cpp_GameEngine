//
// Created by boeken on 8/25/26.
//

#ifndef GAMEENGINE_COLLISIONDATASTRUCTURES_H
#define GAMEENGINE_COLLISIONDATASTRUCTURES_H

namespace GameEngine
{
    struct RectShape
    {
        RectShape(float left, float right, float top, float bottom)
            : Left{left}, Right{right}, Top{top}, Bottom{bottom}
        {}
        RectShape() =default;
        float Left{};
        float Right{};
        float Top{};
        float Bottom{};
    };
}

#endif //GAMEENGINE_COLLISIONDATASTRUCTURES_H
