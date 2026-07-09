#pragma once

#include "Component.h"
#include "GameObject.h"
#include "IMoveable.h"

class PlayerMovement : public GameEngine::Component, public IMoveable
{
public:
    PlayerMovement(GameEngine::GameObject* parent, float speed);

    void Move(glm::vec3 direction) override;
private:
    float m_speed{10};
public:
    PlayerMovement(const PlayerMovement& other) = delete;
	PlayerMovement(PlayerMovement&& other) = delete;
	PlayerMovement& operator=(const PlayerMovement& other) = delete;
	PlayerMovement& operator=(PlayerMovement&& other) = delete;
};