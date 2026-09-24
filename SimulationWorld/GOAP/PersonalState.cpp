#include "PersonalState.h"

#include <stdexcept>

namespace SimWorld
{
    void PersonalState::Set(PersonalKey key, int value)
    {
        m_values[key] = value;
    }

    void PersonalState::Erase(PersonalKey key)
    {
        m_values.erase(key);
    }

    bool PersonalState::Has(PersonalKey key) const
    {
        return m_values.contains(key);
    }

    int PersonalState::Get(PersonalKey key) const
    {
        const auto it = m_values.find(key);
        if (it == m_values.end())
        {
            throw std::out_of_range("Personal state key is not initialized");
        }
        return it->second;
    }

    const std::unordered_map<PersonalKey, int>& PersonalState::Values() const
    {
        return m_values;
    }
}
