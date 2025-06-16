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
    strcpy(name, active_entity->GetName().c_str());

    ImGui::Begin("Inspector");

    ImGui::PushItemWidth(-1);
    if(ImGui::InputText("##INSPECTOR_ENTITY_NAME", name, 128))
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

