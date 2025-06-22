#include "Console.hpp"
#include "Hierarchy.hpp"
#include "imgui.h"
#include "Script.hpp"

void Console::Update()
{
    ImGui::Begin("Console");


    for(auto const& entity : Hierarchy::GetEntities())
    {


        for(auto const& script : entity.scripts)
        {
            if(script->info_messages.size() > 0)
                ImGui::TextColored({1.0, 0.0, 1.0, 1.0}, "%s", script->GetName().c_str());

            for(auto const& message : script->info_messages)
            {
                ImGui::TextColored({1.0, 0.0, 0.0, 1.0}, "%s", message.c_str());
            }
        }
    }

    ImGui::End();
}

