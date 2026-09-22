//
// Created by boeken-work on 9/20/26.
//

#include "Inventory.h"

#include <cassert>

namespace SimWorld
{
    Inventory::Inventory()
        : m_items()
    {
    }

    bool Inventory::Remove(ItemType type, int amount)
    {
        if (amount <= 0) return false;

        if (!Has(type, amount))
        {
            return false;
        }

        m_items[type] -= amount;
        return true;
    }

    void Inventory::Add(ItemType type, int amount)
    {
        if (amount <= 0) return;
        m_items[type] += amount;
    }

    bool Inventory::Transfer(Inventory& other, ItemType type, int amount)
    {
        if (!Remove(type, amount))
        {
            return false;
        }

        other.Add(type, amount);
        return true;
    }

    bool Inventory::Has(ItemType type, int amount) const
    {
        if (amount < 0)
        {
            return false;
        }

        auto it = m_items.find(type);
        if (it == m_items.end())
        {
            return amount == 0;
        }

        return it->second >= amount;
    }

    int Inventory::GetQuantity(ItemType type) const
    {
        auto it = m_items.find(type);
        return it == m_items.end() ? 0 : it->second;
    }
} // SimWorld