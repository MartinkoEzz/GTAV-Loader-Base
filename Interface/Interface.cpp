#include "Interface.hpp"
#include "../Globals.hpp"
#include "../ImGui/imgui.h"
#include "../ImGui/imgui_internal.h"
#include "../Utility/Utility.hpp"
#include <shellapi.h>
#include <string>
void Interface::Render() {
    if (!g_Running)
        return;

    // HOW TO USE
    // Here you gonna edit User Interface, for dll download or discord url check Globals.hpp.
    // Enjoy this base 
    // ORIGINAL BASE HAS BEEN MADE BY STASH, I JUST FIXED IT AND IMPROVED!!!
    // Discord contact: kim_jong_m

    ImGui::SetNextWindowPos(ImVec2(g_WindowPosition.x, g_WindowPosition.y), ImGuiCond_Once);
    ImGui::SetNextWindowSize(ImVec2(g_WindowSize.x, g_WindowSize.y));
    ImGui::SetNextWindowBgAlpha(1.0f);
    
    ImGui::Begin(g_Name.c_str(), &g_Running, g_WindowFlags);
    {
        if (g_Authed)
        {
            ImGui::SetCursorPosX((ImGui::GetContentRegionAvail().x - ImGui::CalcTextSize("Hi there!").x) * 0.5f);
            ImGui::Text("Hi there!");
            ImGui::SetCursorPosX((ImGui::GetContentRegionAvail().x - ImGui::CalcTextSize("Inject").x) * 0.5f);
            if (ImGui::Button("Inject")) { Utility::Inject(Utility::GetLoaderPath() + OBFUSCATE("\\Menu.dll"), "xR@ld2odcOIeYh2nHym$VUjTKd#o5hmD24qd4f42A82ATCwmJ0"); }
            ImGui::SetCursorPosX((ImGui::GetContentRegionAvail().x - ImGui::CalcTextSize("Join Discord").x) * 0.5f);
            if (ImGui::Button("Join Discord")) { ShellExecute(0, 0, g_DiscordURL.c_str(), 0, 0, SW_SHOW); }
        }
        else
        // i disabled key window for now, if you want to have key just go to Globals.hpp and set g_Authed to false and add pastebin to your key!
        {
            ImGui::InputTextWithHint(OBFUSCATE("###key_input"), OBFUSCATE("Key"), g_Key, 55);
            if (ImGui::Button("Login"))
            {
                if (g_Key == Utility::GetKey())
                    g_Authed = true;
                else {
                    MessageBox(NULL, TEXT("Key is incorrect!"), TEXT("Error"), MB_OK);
                }
            }
            ImGui::SameLine();
            if (ImGui::Button("Get Key")) { ShellExecute(0, 0, g_LinkvertiseURL.c_str(), 0, 0, SW_SHOW); }
            if (ImGui::Button("Join Discord")) { ShellExecute(0, 0, g_DiscordURL.c_str(), 0, 0, SW_SHOW); }
        }
    }
    ImGui::End();
}

void Interface::Initialize(LPDIRECT3DDEVICE9 device)
{
    g_Device = device;

    // Colors
    ImGui::GetStyle();

    if (g_WindowPosition.x == 0)
    {
        RECT ScreenRectangle{};
        GetWindowRect(GetDesktopWindow(), &ScreenRectangle);
        g_ScreenResolution = ImVec2(float(ScreenRectangle.right), float(ScreenRectangle.bottom));
        g_WindowPosition = (g_ScreenResolution - g_WindowSize) * 0.5f;
    }
}