#pragma once
#include <d3d9.h>
#include "../ImGui/imgui.h"

namespace Interface 
{
	void Initialize(LPDIRECT3DDEVICE9);
	void Render();
}

namespace Interface
{
	inline LPDIRECT3DDEVICE9 g_Device;
	inline ImVec2 g_ScreenResolution{ 0.f, 0.f };
	inline ImVec2 g_WindowPosition{ 0.f, 0.f };
	inline ImVec2 g_WindowSize{ 350.f, 150.f };
	inline DWORD g_WindowFlags = ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar;
	inline ImFont* bigFont = NULL;
}