#include "Hierarchy.hpp"
#include "Scripting/Script.hpp"
#include "imgui.h"
#include "Entity.hpp"
#include <vector>
#include <string>
std::vector<Entity> Hierarchy::entities;

void Hierarchy::Update()
{
    static unsigned int count = 0;
    ImGui::Begin("Hierarchy");

    if(ImGui::Button("Create Collection", ImVec2(-1, 25)))
    {
        count++;
        std::string id = "New Collection (" + std::to_string(count) + ")";

        Hierarchy::AddEntity(id.c_str());
    }

    ImGui::Separator();

    for(auto& entity : entities)
    {
        if(ImGui::Button(entity.GetName().c_str(), ImVec2(-1, 25)))
        {
            Inspector::SetActiveEntity(&entity);
        }

        // Do we really want to execute it here?
        entity.ExecuteAll();
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

const std::vector<Entity>& Hierarchy::GetEntities()
{
    return entities;
}
