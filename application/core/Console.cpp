#include "Console.hpp"
#include "imgui.h"
#include "imgui_internal.h"
#include <unordered_map>
#include <vector>
#include <iomanip>

std::vector<Console::Message> Console::messages;

void Console::AddMessage(Message message)
{
    std::time_t now = std::time(nullptr);
    std::tm* time = std::localtime(&now);
    char text[9];

    std::snprintf(text, sizeof(text), "%02d:%02d:%02d", time->tm_hour, time->tm_min, time->tm_sec);

    message.time = text;
    messages.push_back(message);
}

void Console::Update()
{
    using namespace ImGui;

    static std::unordered_map<MessageType, ImVec4> colors =
    {
        {MessageType::Error,    {1.0, 0.0, 0.0, 1.0}},
        {MessageType::Warning,  {1.0, 0.5, 0.2, 1.0}},
        {MessageType::Info,     {0.0, 1.0, 0.0, 1.0}}
    };

    ImGui::Begin("Console");

    for(int i = 0; i < messages.size(); i++)
    {
        const Message& message = messages.at(i);
        ImGui::PushID(&message);
        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 4));
        
        if(ImGui::Button("Remove", {0, 0}))
        {
            messages.erase(messages.begin() + i);
        }

        ImGui::SameLine();

        ImGui::TextColored(colors[message.type], "%s", message.title.c_str());
        
        ImGui::SameLine();
        
        ImGui::SetCursorPosX(GetCursorPosX() + ImMax(0.0f, GetContentRegionAvail().x - CalcTextSize(message.title.c_str()).x));
        ImGui::Text("%s", message.time.c_str());

        ImGui::BeginChild("ErrorMessages", ImVec2(-1, 50));

        ImGui::Text("%s", message.content.c_str());

        ImGui::EndChild();
        ImGui::PopStyleVar();
        ImGui::PopID();
    }

    ImGui::End();
}

