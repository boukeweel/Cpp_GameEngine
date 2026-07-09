#pragma once

namespace GameEngine
{
    class ICommand
    {
    public:
        ICommand() = default;
        virtual ~ICommand() = default;
        virtual void Execute() = 0;

        ICommand(const ICommand& other) = delete;
		ICommand(ICommand&& other) = delete;
		ICommand& operator=(const ICommand& other) = delete;
		ICommand& operator=(ICommand&& other) = delete;
    };

}