#include "MoveCommand.h"
#include "IMoveable.h"

MoveCommand::MoveCommand(IMoveable* target, glm::vec3 direction) : m_target(target), m_direction(direction){}

void MoveCommand::Execute(){
    m_target->Move(m_direction);
}