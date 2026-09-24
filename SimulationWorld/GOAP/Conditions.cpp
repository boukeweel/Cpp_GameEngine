#include "Conditions.h"

#include <stdexcept>

namespace SimWorld
{
    StateValue StateValue::Constant(int value)
    {
        StateValue result;
        result.source = ValueSource::Constant;
        result.constant = value;
        return result;
    }

    StateValue StateValue::Personal(PersonalKey key)
    {
        StateValue result;
        result.source = ValueSource::Personal;
        result.personalKey = key;
        return result;
    }

    StateValue StateValue::World(WorldKey key)
    {
        StateValue result;
        result.source = ValueSource::World;
        result.worldKey = key;
        return result;
    }

    int StateValue::Resolve(const PersonalState& personalState,
                            const WorldState& worldState) const
    {
        switch (source)
        {
            case ValueSource::Constant:
                return constant;
            case ValueSource::Personal:
                return personalState.Get(personalKey);
            case ValueSource::World:
                return worldState.Get(worldKey);
        }

        throw std::logic_error("Unknown state value source");
    }

    bool Condition::IsSatisfied(const PersonalState& personalState,
                                const WorldState& worldState) const
    {
        const int leftValue = left.Resolve(personalState, worldState);
        const int rightValue = right.Resolve(personalState, worldState);

        switch (comparison)
        {
            case Comparison::Equal:
                return leftValue == rightValue;
            case Comparison::NotEqual:
                return leftValue != rightValue;
            case Comparison::Less:
                return leftValue < rightValue;
            case Comparison::LessOrEqual:
                return leftValue <= rightValue;
            case Comparison::Greater:
                return leftValue > rightValue;
            case Comparison::GreaterOrEqual:
                return leftValue >= rightValue;
        }

        return false;
    }

    void Effect::Apply(PersonalState& personalState, WorldState& worldState) const
    {
        const int operand = value.Resolve(personalState, worldState);

        if (targetSource == ValueSource::Personal)
        {
            const int current = personalState.Has(personalKey)
                ? personalState.Get(personalKey)
                : 0;

            switch (operation)
            {
                case EffectOperation::Set:
                    personalState.Set(personalKey, operand);
                    break;
                case EffectOperation::Add:
                    personalState.Set(personalKey, current + operand);
                    break;
                case EffectOperation::Subtract:
                    personalState.Set(personalKey, current - operand);
                    break;
            }
            return;
        }

        const int current = worldState.Has(worldKey) ? worldState.Get(worldKey) : 0;
        switch (operation)
        {
            case EffectOperation::Set:
                worldState.Set(worldKey, operand);
                break;
            case EffectOperation::Add:
                worldState.Set(worldKey, current + operand);
                break;
            case EffectOperation::Subtract:
                worldState.Set(worldKey, current - operand);
                break;
        }
    }
}
