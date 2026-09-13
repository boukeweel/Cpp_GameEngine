//
// Created by boeken on 9/12/26.
//

#ifndef SimWorld_STATES_H
#define SimWorld_STATES_H
#include <unordered_map>

namespace SimWorld {
    enum class PersonKeys {
        HasFood,
        Hunger, // 0 = fed, 1 = hungry, 2 = starving
    };

    using PersonState = std::unordered_map<PersonKeys, int>;
}

#endif //SimWorld_STATES_H
