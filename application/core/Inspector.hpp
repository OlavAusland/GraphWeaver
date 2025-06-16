#pragma once
#include "Entity.hpp"

class Inspector
{
private:
    static Entity* active_entity;
public:
    Inspector() = delete;

    static void SetActiveEntity(Entity* entity);
    static Entity* GetActiveEntity();
    static void Update();
};
