#ifndef INPUT_DATA_H
#define INPUT_DATA_H

#include "ICommand.h"
#include <algorithm>
#include <cstddef>
#include <memory>
#include <vector>
#include <SDL_events.h>

namespace GameEngine
{
    class ICommand;

    struct InputAction
    {
        std::vector<SDL_Scancode> keyBoardKeys;

        bool HasKeyBoardKey(SDL_Scancode key) const
        {
            return std::find(keyBoardKeys.begin(), keyBoardKeys.end(),key) != keyBoardKeys.end();
        }

        bool operator==(const InputAction& other) const
        {
            if(keyBoardKeys.size() != other.keyBoardKeys.size())
                return false;

            if(!keyBoardKeys.empty())
            {
                for(size_t i = 0; i < keyBoardKeys.size(); ++i){
                    if(keyBoardKeys[i] != other.keyBoardKeys[i]){
                        return false;
                    }
                }
            }
            return true;
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
        CommandInfo(InputStates buttonState, const InputAction& action, std::unique_ptr<ICommand> command)
			: inputState(buttonState), Action(action), command(std::move(command))
		{}

        InputStates inputState{};
        InputAction Action{};
        std::unique_ptr<ICommand> command;

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

#endif //INPUT_DATA_H