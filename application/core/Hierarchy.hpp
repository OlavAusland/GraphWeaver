#pragma once
#include <vector>
#include "Entity.hpp"
#include "Inspector.hpp"


class Hierarchy
{
private:
    static std::vector<Entity> entities;
public:
    Hierarchy() = delete;

    static void AddEntity(std::string name);
    static Entity* GetEntity(std::string name);
    static void Update();
};
