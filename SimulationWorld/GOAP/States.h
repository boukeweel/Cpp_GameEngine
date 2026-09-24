//
// Created by boeken on 9/12/26.
//

#ifndef SimWorld_STATES_H
#define SimWorld_STATES_H
namespace SimWorld {
    enum class PersonalKey {
        Hunger,
        FoodQuantity,
        Money,
        HasJob,
        ShouldWork,
        FindJob,
    };

    enum class WorldKey {
        FoodPrice,
        FoodAvailable,
        StoreAvailable,
    };
}

#endif //SimWorld_STATES_H
