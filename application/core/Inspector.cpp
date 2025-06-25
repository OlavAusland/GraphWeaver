#include "Inspector.hpp"
#include "Entity.hpp"
#include "imgui.h"
#include <string.h>

Entity* Inspector::active_entity = nullptr;

void Inspector::SetActiveEntity(Entity* entity)
{
    active_entity = entity;
}

Entity* Inspector::GetActiveEntity()
{
    return active_entity;
}

void Inspector::Update()
{
    if(active_entity == nullptr) { return; }

    char name[128] = "\0";
    strncpy(name, active_entity->GetName().c_str(), sizeof(name));

    ImGui::Begin("Inspector");

    ImGui::PushItemWidth(-1);
    if(ImGui::InputText("##INSPECTOR_ENTITY_NAME", name, sizeof(name)))
    {
        active_entity->SetName(name);
    }

    ImGui::Separator();

    for(auto const& script : active_entity->scripts)
    {
        ImGui::Checkbox(script->GetName().c_str(), script->GetIsEnableRef());
    }

    ImGui::End();
}

