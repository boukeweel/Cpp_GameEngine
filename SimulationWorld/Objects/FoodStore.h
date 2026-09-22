//
// Created by boeken on 9/21/26.
//

#ifndef GAMEENGINE_FOODSTORE_H
#define GAMEENGINE_FOODSTORE_H

#include "Component.h"
#include "Wallet.h"
#include "Inventory.h"

namespace SimWorld {
    ///The class that lets a person buy food (unlimited stock) using their wallet
    class FoodStore : public GameEngine::Component
    {
    public:
        FoodStore(GameEngine::GameObject* owner,int pricePerFood);

        bool Buy(Wallet& buyerWallet, Inventory& buyerInventory, int amount);

        int GetPrice() const;

    private:
        int m_pricePerFood;
    };
}



#endif //GAMEENGINE_FOODSTORE_H