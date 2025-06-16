#include "Hierarchy.hpp"
#include "Scripting/Script.hpp"
#include "imgui.h"
#include "Entity.hpp"
#include <vector>
#include <string>
std::vector<Entity> Hierarchy::entities;

void Hierarchy::Update()
{
    ImGui::Begin("Hierarchy");

    for(auto& entity : entities)
    {
        if(ImGui::Button(entity.GetName().c_str(), ImVec2(-1, 20)))
        {
            Inspector::SetActiveEntity(&entity);
        }
    }

    ImGui::End();
}

void Hierarchy::AddEntity(std::string name)
{
    entities.push_back(Entity(name));
}

Entity* Hierarchy::GetEntity(std::string name)
{
    for(auto& entity : entities)
    {
        if(entity.GetName() == name)
        {
            return &entity;
        }
    }

    return  nullptr;
}
