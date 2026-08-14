#ifndef SG_PLAYER_MOVEMENT_H
#define SG_PLAYER_MOVEMENT_H

#include "Component.h"
#include "GameObject.h"
#include "IMoveable.h"

namespace SurvivalGame
{
    class SGPlayerMovement : public GameEngine::Component, public IMoveable
    {
    public:
        SGPlayerMovement(GameEngine::GameObject* parent, float speed);
    
        void Move(glm::vec3 direction) override;
    private:
        float m_speed{10};
    public:
        SGPlayerMovement(const SGPlayerMovement& other) = delete;
    	SGPlayerMovement(SGPlayerMovement&& other) = delete;
    	SGPlayerMovement& operator=(const SGPlayerMovement& other) = delete;
    	SGPlayerMovement& operator=(SGPlayerMovement&& other) = delete;
    };
}

#endif //SG_PLAYER_MOVEMENT_H