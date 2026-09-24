#ifndef SIMWORLD_WORLDSTATE_H
#define SIMWORLD_WORLDSTATE_H

#include <unordered_map>

#include "States.h"

namespace SimWorld
{
    class WorldState
    {
    public:
        void Set(WorldKey key, int value);
        [[nodiscard]] bool Has(WorldKey key) const;
        [[nodiscard]] int Get(WorldKey key) const;
        [[nodiscard]] const std::unordered_map<WorldKey, int>& Values() const;

    private:
        std::unordered_map<WorldKey, int> m_values;
    };
}

#endif // SIMWORLD_WORLDSTATE_H
