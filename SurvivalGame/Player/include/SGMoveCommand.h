#ifndef VS_MOVE_COMMAND_H
#define VS_MOVE_COMMAND_H

#include "ICommand.h"
#include <glm/vec3.hpp>

class IMoveable;
namespace SurvivalGame
{
    class SGMoveCommand : public GameEngine::ICommand{
    public:
        SGMoveCommand(IMoveable* target, glm::vec3 Direction);
        void Execute() override;

    private:
        IMoveable* m_target;
        glm::vec3 m_direction;
    };
}

#endif //MOVE_COMMAND_H