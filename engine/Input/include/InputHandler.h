#pragma once

#include "Singleton.h"
#include <memory>
#include <vector>
#include <SDL_events.h>

namespace GameEngine
{
    struct InputAction;
    struct CommandInfo;
    enum class InputStates;
    class Command;
    enum class InputKeys;

    class InputHandler final : public Singleton<InputHandler>
    {
    public:
        InputHandler();
        ~InputHandler();

        bool ProccesInput();

        void AddCommand(const InputKeys& key, InputStates state, std::unique_ptr<Command> command);


        void RemoveAllCommands();
		void RemoveCommand(const InputKeys& key);

		void AddInput(const InputKeys& key, const InputAction& actions);
		void RemoveInput(const InputKeys& key);

        bool HandelKeyBoardEvent(const SDL_Event& event) const;
		void HandleKeyboardContinually() const;
    private:
        std::vector<InputAction> m_inputButtons;
        std::vector<CommandInfo> m_commands;
    };
}