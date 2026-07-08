#include "InputHandler.h"
#include "Command.h"
#include "InputData.h"
#include <SDL_events.h>
#include <SDL_keyboard.h>
#include <SDL_stdinc.h>
#include <algorithm>
#include <memory>
#include <utility>

namespace GameEngine 
{
    bool InputHandler::ProccesInput()
    {
        HandleKeyboardContinually();
        
        SDL_Event e;
        while(SDL_PollEvent(&e))
        {
            if(e.type == SDL_QUIT){
                return false;
            }
            if(HandelKeyBoardEvent(e)){
                continue;
            }
        }
        return true;    
    }

    bool InputHandler::HandelKeyBoardEvent(const SDL_Event& event) const
    {
        switch (event.type) 
        {
            case SDL_KEYDOWN:
            case SDL_KEYUP:
                const InputStates inputState = event.type == SDL_KEYDOWN ? InputStates::Down : InputStates::Up;
                for (auto&& command : m_commands) 
                {
                    if(event.key.repeat)
                        continue;

                    command.TryExecutedKeyBoard(inputState, event.key.keysym.scancode);
                }
                return true;
        }
        return false;
    }

    void InputHandler::HandleKeyboardContinually() const
    {
        const Uint8* keyboardState = SDL_GetKeyboardState(nullptr);

        for (auto&& commandInfo : m_commands)
        {
            if(commandInfo.inputState != InputStates::Held)
                continue;

            for (auto&& keyboardKey : commandInfo.Action.keyBoardKeys)
            {
                if(keyboardState[keyboardKey])
                {
                    commandInfo.command->Execute();
                    break;
                }
            }

        }
    }

    void InputHandler::AddCommand(const InputKeys& key, InputStates state, std::unique_ptr<Command> command)
    {
        m_commands.emplace_back(state,m_inputButtons.at(key), std::move(command));
    }

    void InputHandler::RemoveAllCommands()
    {
        m_commands.clear();
    }

    void InputHandler::RemoveCommand(const InputKeys& key)
    {
        m_commands.erase(std::remove_if(m_commands.begin(),m_commands.end(),
        [this,&key](const CommandInfo& cmd) { return cmd.Action == m_inputButtons.at(key); }),
        m_commands.end());

    }

    void InputHandler::AddInput(const InputKeys& key, const InputAction& actions){
        m_inputButtons[key] = actions;
    }

    void InputHandler::RemoveInput(const InputKeys& key){
        m_inputButtons.erase(key);
    }
}