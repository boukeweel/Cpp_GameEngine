#pragma once
#include "Command.h"
#include <algorithm>
#include <memory>
#include <vector>
#include <SDL_events.h>

namespace GameEngine
{
    class Command;

    struct InputAction
    {
        std::vector<SDL_Scancode> keyBoardKeys;

        bool HasKeyBoardKey(SDL_Scancode key) const
        {
            return std::find(keyBoardKeys.begin(), keyBoardKeys.end(),key) != keyBoardKeys.end();
        }
    };

    enum class InputStates
    {
        Down,
        Held,
        Up,
    };

    struct CommandInfo
    {
        CommandInfo(InputStates buttonState, int controllerIndex, const InputAction& action, std::unique_ptr<Command> command)
			: inputState(buttonState), Action(action), command(std::move(command))
		{}

        InputStates inputState{};
        InputAction Action{};
        std::unique_ptr<Command> command;

        void TryExecutedKeyBoard(InputStates checkState, SDL_Scancode key) const
        {
            if(inputState != checkState)
                return;
            if(!Action.HasKeyBoardKey(key))
                return;

            command->Execute();
        }
    };

    
    //todo dont know if this is the correct method but going for this method for now
    // untill something makes me swap it or I find a better option.
    enum class InputKeys
    {
        ARROW_UP,
        ARROW_DOWN,
        ARROW_LEFT,
        ARROW_RIGHT,

        KEY_W,
        KEY_S,
        KEY_A,
        KEY_D,
        KEY_SPACE,
    };
}   