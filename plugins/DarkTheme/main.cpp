#include <stdio.h>
#include "EventManager.hpp"
#include "PluginManager.hpp"
#include "imgui.h"
#include "SDL3/SDL.h"
#include <vector>
#include <tuple>

void SetStyle()
{
    ImGuiStyle& style = ImGui::GetStyle();
    
    // Tab Styling
    style.TabRounding = 0.0;
    style.TabBorderSize = 0.0;
    style.TabBarOverlineSize = 0.0;
    style.WindowBorderSize = 0;
    style.FramePadding = ImVec2(5, 5);

    style.FrameRounding = 4;
    style.FrameBorderSize = 0.0;
    
    style.ItemSpacing = ImVec2(0, 15);
    style.ItemInnerSpacing = ImVec2(0, 0);


    style.Colors[ImGuiCol_Button] = ImVec4(0.1, 0.1, 0.1, 1.0);
    style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.125, 0.125, 0.125, 1.0);
    style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.075, 0.075, 0.075, 1.0);

    style.Colors[ImGuiCol_TabSelected] = style.Colors[ImGuiCol_WindowBg];
    style.Colors[ImGuiCol_Tab] = ImVec4(0.1, 0.1, 0.1, 1.0);
    style.Colors[ImGuiCol_TabHovered] = ImVec4(0.001, 0.001, 0.001, 1.0);
    style.Colors[ImGuiCol_TabDimmedSelected] = style.Colors[ImGuiCol_TabSelected];
    style.Colors[ImGuiCol_TabDimmed]    = style.Colors[ImGuiCol_Tab];
    style.Colors[ImGuiCol_TitleBg] = ImVec4(1.0, 0.0, 0.0, 1.0);

    style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.125, 0.125, 0.125, 1.0);
    style.Colors[ImGuiCol_TitleBg] = style.Colors[ImGuiCol_TitleBgActive];

    style.Colors[ImGuiCol_FrameBg] = style.Colors[ImGuiCol_Button];
    style.Colors[ImGuiCol_FrameBgHovered] = style.Colors[ImGuiCol_ButtonHovered];
    style.Colors[ImGuiCol_FrameBgActive] = style.Colors[ImGuiCol_ButtonActive];

    style.Colors[ImGuiCol_CheckMark] = ImVec4(0.9, 0.9, 0.9, 1.0);

}

static ImGuiStyle original_style;

__attribute__((constructor))
void Entry()
{
    original_style = ImGui::GetStyle();
    printf("[ INFO ] Loaded %s\n", __func__);
    SetStyle();
}

__attribute__((destructor))
void Exit()
{
    ImGuiStyle& style = ImGui::GetStyle();
    style = original_style;
    printf("[ INFO ] Unloaded %s\n", __func__);
}

