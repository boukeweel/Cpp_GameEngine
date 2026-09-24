#ifndef SIMWORLD_CONDITIONS_H
#define SIMWORLD_CONDITIONS_H

#include "PersonalState.h"
#include "WorldState.h"

namespace SimWorld
{
    enum class Comparison
    {
        Equal,
        NotEqual,
        Less,
        LessOrEqual,
        Greater,
        GreaterOrEqual
    };

    enum class ValueSource
    {
        Constant,
        Personal,
        World
    };

    struct StateValue
    {
        ValueSource source{ValueSource::Constant};
        int constant{0};
        PersonalKey personalKey{};
        WorldKey worldKey{};

        static StateValue Constant(int value);
        static StateValue Personal(PersonalKey key);
        static StateValue World(WorldKey key);

        [[nodiscard]] int Resolve(const PersonalState& personalState,
                                   const WorldState& worldState) const;
    };

    struct Condition
    {
        StateValue left;
        Comparison comparison{Comparison::Equal};
        StateValue right;

        [[nodiscard]] bool IsSatisfied(const PersonalState& personalState,
                                       const WorldState& worldState) const;
    };

    enum class EffectOperation
    {
        Set,
        Add,
        Subtract
    };

    struct Effect
    {
        ValueSource targetSource{ValueSource::Personal};
        PersonalKey personalKey{};
        WorldKey worldKey{};
        EffectOperation operation{EffectOperation::Set};
        StateValue value;

        void Apply(PersonalState& personalState, WorldState& worldState) const;
    };
}

#endif // SIMWORLD_CONDITIONS_H
