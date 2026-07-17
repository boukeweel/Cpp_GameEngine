#ifndef MOVE_COMMAND_H
#define MOVE_COMMAND_H

#include "ICommand.h"
#include <glm/vec3.hpp>

class IMoveable;

class MoveCommand : public GameEngine::ICommand{
public:
    MoveCommand(IMoveable* target, glm::vec3 Direction);
    void Execute() override;

private:
    IMoveable* m_target;
    glm::vec3 m_direction;
};

#endif //MOVE_COMMAND_H