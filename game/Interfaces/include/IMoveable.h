#pragma once
#include <glm/vec3.hpp>

class IMoveable
{
public:
    virtual void Move(glm::vec3 direction) = 0;
    virtual ~IMoveable() = default;
};