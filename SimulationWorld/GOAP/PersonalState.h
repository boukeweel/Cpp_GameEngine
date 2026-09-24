#ifndef SIMWORLD_PERSONALSTATE_H
#define SIMWORLD_PERSONALSTATE_H

#include <unordered_map>

#include "States.h"

namespace SimWorld
{
    class PersonalState
    {
    public:
        void Set(PersonalKey key, int value);
        void Erase(PersonalKey key);
        [[nodiscard]] bool Has(PersonalKey key) const;
        [[nodiscard]] int Get(PersonalKey key) const;
        [[nodiscard]] const std::unordered_map<PersonalKey, int>& Values() const;

    private:
        std::unordered_map<PersonalKey, int> m_values;
    };
}

#endif // SIMWORLD_PERSONALSTATE_H
