#pragma once
#include <iostream>
#include <windows.h>
#include <thread>

#include <d3d9.h>
#pragma comment(lib,"d3d9.lib")

#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_dx9.h"
#include "ImGui/imgui_impl_win32.h"

HWND g_MainHWND = nullptr;

LPDIRECT3DDEVICE9 g_Device;
D3DPRESENT_PARAMETERS g_Parameters;
LPDIRECT3D9 g_Direct;

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

bool CreateDeviceD3D(HWND hWnd)
{
    if ((g_Direct = Direct3DCreate9(D3D_SDK_VERSION)) == NULL)
        return false;

    // Create the D3DDevice
    ZeroMemory(&g_Parameters, sizeof(g_Parameters));
    g_Parameters.Windowed = TRUE;
    g_Parameters.SwapEffect = D3DSWAPEFFECT_DISCARD;
    g_Parameters.BackBufferFormat = D3DFMT_UNKNOWN;
    g_Parameters.EnableAutoDepthStencil = TRUE;
    g_Parameters.AutoDepthStencilFormat = D3DFMT_D16;
    g_Parameters.PresentationInterval = D3DPRESENT_INTERVAL_ONE;           // Present with vsync
    if (g_Direct->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &g_Parameters, &g_Device) < 0)
        return false;
    return true;
}

void CleanupDeviceD3D()
{
    if (g_Device)
    { 
        g_Device->Release();
        g_Device = NULL;
    }
    if (g_Direct)
    { 
        g_Direct->Release();
        g_Direct = NULL;
    }
}

void ResetDevice()
{
    ImGui_ImplDX9_InvalidateDeviceObjects();
    HRESULT Result = g_Device->Reset(&g_Parameters);
    if (Result == D3DERR_INVALIDCALL)
        IM_ASSERT(0);
    ImGui_ImplDX9_CreateDeviceObjects();
}