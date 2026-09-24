#include "WorldState.h"

#include <stdexcept>

namespace SimWorld
{
    void WorldState::Set(WorldKey key, int value)
    {
        m_values[key] = value;
    }

    bool WorldState::Has(WorldKey key) const
    {
        return m_values.contains(key);
    }

    int WorldState::Get(WorldKey key) const
    {
        const auto it = m_values.find(key);
        if (it == m_values.end())
        {
            throw std::out_of_range("World state key is not initialized");
        }
        return it->second;
    }

    const std::unordered_map<WorldKey, int>& WorldState::Values() const
    {
        return m_values;
    }
}
