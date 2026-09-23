//
// Created by boeken-work on 9/20/26.
//

#ifndef GAMEENGINE_INVENTORY_H
#define GAMEENGINE_INVENTORY_H

#include <unordered_map>

#include "Person.h"

namespace SimWorld
{
    enum class ItemType
    {
        Food
    };

    ///The class that will hold the amounts of items (food, etc.) someone owns
    class Inventory
    {
    public:
        Inventory(Person* person);

        bool Remove(ItemType type, int amount);
        void Add(ItemType type, int amount);
        bool Transfer(Inventory& other, ItemType type, int amount);

        bool Has(ItemType type, int amount) const;
        int GetQuantity(ItemType type) const;

    private:
        std::unordered_map<ItemType, int> m_items;
        Person* m_Person;
    };
} // SimWorld

#endif //GAMEENGINE_INVENTORY_H