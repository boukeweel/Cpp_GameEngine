#include "SGMoveCommand.h"
#include "IMoveable.h"

namespace SurvivalGame
{
    SGMoveCommand::SGMoveCommand(IMoveable* target, glm::vec3 direction) : m_target(target), m_direction(direction){}

    void SGMoveCommand::Execute(){
        m_target->Move(m_direction);
    }
}