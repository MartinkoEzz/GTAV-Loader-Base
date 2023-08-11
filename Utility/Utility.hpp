#pragma once
#include <curl.h>
#include <string>
#include <filesystem>
#include "../Globals.hpp"
#include "Obfuscate.hpp"
#include <d3dx9tex.h>
#pragma comment(lib, "D3dx9")
namespace Utility
{
	typedef size_t(*Write)(char*, size_t, size_t, std::string*);
	inline void reduceString(std::string& input, int size)
	{
		int lastSpace = 0;
		int lastNewLine = 0;
		for (int i = 0; i < input.length(); i++)
		{
			if (input[i] == '\n')
			{
				lastNewLine = i;
				continue;
			}
			if (input[i] == 32)
			{
				lastSpace = i;
			}
			if (i - lastNewLine >= size)
			{
				input.insert(lastSpace + 1, "\n");
				lastNewLine = i;
			}
		}
	}
	inline void ImageToggleButton(const char* str_id, int* allTabNumbers, int setTabNumber, void* image, ImVec2 size) //toggle button function
	{
		ImVec2 p = ImGui::GetCursorScreenPos();
		ImDrawList* draw_list = ImGui::GetWindowDrawList();

		float height = size.y;
		float width = size.x;
		if (ImGui::InvisibleButton(str_id, ImVec2(width, height)))
		{
			*allTabNumbers = setTabNumber;
		}
		if (ImGui::IsItemHovered())
			draw_list->AddRectFilled(p, ImVec2(p.x + width, p.y + height), (ImU32)ImColor(0, 0, 0, 255), 0);
		if (*allTabNumbers == setTabNumber)
		{
			draw_list->AddRectFilled(p, ImVec2(p.x + width, p.y + height), (ImU32)ImColor(0, 0, 100, 255), 0);
			draw_list->AddImage(image, p, ImVec2(p.x + width, p.y + height));
		}
		else
		{
			draw_list->AddImage(image, p, ImVec2(p.x + width, p.y + height));
		}

	}
	inline static std::size_t WriteData(void* ptr, std::size_t size, std::size_t nmemb, void* stream)
	{
		auto written = fwrite(ptr, size, nmemb, (FILE*)stream);
		return written;
	}

	inline std::string Request(std::string url)
	{
		CURLcode res_code = CURLE_FAILED_INIT;
		CURL* curl = curl_easy_init();
		std::string result;

		curl_global_init(CURL_GLOBAL_ALL);

		if (curl) {
			curl_easy_setopt(curl,
				CURLOPT_WRITEFUNCTION,
				static_cast <Write> ([](char* contents, size_t size,
					size_t nmemb, std::string* data) -> size_t {
						size_t new_size = size * nmemb;
			if (data == NULL) {
				return 0;
			}
			data->append(contents, new_size);
			return new_size;
					}));
			curl_easy_setopt(curl, CURLOPT_WRITEDATA, &result);
			curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
			curl_easy_setopt(curl, CURLOPT_USERAGENT, OBFUSCATE("Cock"));

			res_code = curl_easy_perform(curl);

			if (res_code != CURLE_OK) {
				return curl_easy_strerror(res_code);
			}

			curl_easy_cleanup(curl);
		}

		curl_global_cleanup();

		return result;
	}
	inline void DownloadFileFromUrl(std::string url, std::string path)
	{
		CURL* curl;
		FILE* fp;
		CURLcode res;
		curl = curl_easy_init();
		if (curl)
		{
			fp = fopen(path.c_str(), "wb");
			curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
			curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteData);
			curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
			curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
			res = curl_easy_perform(curl);
			curl_easy_cleanup(curl);
			fclose(fp);
		}
	}

	inline void Inject(std::string path, std::string atom)
	{
		if (!FindWindowA(NULL, "Grand Theft Auto V"))
		{
			MessageBox(NULL, TEXT("Open GTA5 First!"), TEXT("Error"), MB_OK);
		}

		// Add Atom
		GlobalAddAtomA(atom.c_str());

		// You want your menu to be injected with this loader, and not xenos, if people grab the dll then they can only inject it with this meaning they need a pastebin key after a linkvertise
		// Paste this code in your Main.cpp in the WHILE(g_Running) loop:
		// xR@ld2odcOIeYh2nHym$VUjTKd#o5hmD24qd4f42A82ATCwmJ0 can be a random string of choice, but make sure to also define that in Interface.cpp on line 22
		//if (GlobalFindAtomA("xR@ld2odcOIeYh2nHym$VUjTKd#o5hmD24qd4f42A82ATCwmJ0") == 0)
		//{
			// They used another injector, you can log this 
			// g_Logger->Info("You used another injector, fuck you!");
			//exit(0);
		//}

		HWND HWND = FindWindowA(NULL, "Grand Theft Auto V"); // HWND (Windows window) by Window Name
		DWORD ProcessID; // A 32-bit unsigned integer, DWORDS are mostly used to store Hexadecimal Addresses
		GetWindowThreadProcessId(HWND, &ProcessID); // Getting our Process ID, as an ex. like 000027AC
		HANDLE Handle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, ProcessID); // Opening the Process with All Access

		// Allocate memory for the dllpath in the target process, length of the path string + null terminator
		LPVOID Path = VirtualAllocEx(Handle, 0, strlen(path.c_str()) + 1, MEM_COMMIT, PAGE_READWRITE);

		// Write the path to the address of the memory we just allocated in the target process
		WriteProcessMemory(Handle, Path, (LPVOID)path.c_str(), strlen(path.c_str()) + 1, 0);

		// Create a Remote Thread in the target process which calls LoadLibraryA as our dllpath as an argument -> program loads our dll
		HANDLE hLoadThread = CreateRemoteThread(Handle, 0, 0,
			(LPTHREAD_START_ROUTINE)GetProcAddress(GetModuleHandleA("Kernel32.dll"), "LoadLibraryA"), Path, 0, 0);

		WaitForSingleObject(hLoadThread, INFINITE); // Wait for the execution of our loader thread to finish

		VirtualFreeEx(Handle, Path, strlen(path.c_str()) + 1, MEM_RELEASE); // Free the memory allocated for our dll path
	}

	inline bool Killswitch()
	{
		return Request(g_KillswitchPaste) == "YES";
	}

	inline std::string GetLoaderPath()
	{
		std::string appdata = std::getenv("appdata");
		std::string path = appdata + OBFUSCATE("\\") + g_Name;
		return path;
	}

	inline void DownloadFiles()
	{
		namespace fs = std::filesystem;
		if (!fs::exists(GetLoaderPath()))
			fs::create_directory(GetLoaderPath());
	}
	inline void DownloadDll()
	{
		while (true)
		{
			if (g_Authed)
			{
				DownloadFileFromUrl(g_DllUrl, GetLoaderPath() + OBFUSCATE("\\Menu.dll"));
				g_Resources_Downloaded = true;
				break;
			}
			Sleep(100);
		}
	}
	inline std::string GetKey()
	{
		return Request(g_KeyPaste);
	}
	// Simple helper function to load an image into a DX9 texture with common settings
	inline bool LoadTextureFromFile(const char* filename, PDIRECT3DTEXTURE9* out_texture, int* out_width, int* out_height, LPDIRECT3DDEVICE9 g_pd3dDevice)
	{
		// Load texture from disk
		PDIRECT3DTEXTURE9 texture;
		HRESULT hr = D3DXCreateTextureFromFileA(g_pd3dDevice, filename, &texture);
		if (hr != S_OK)
			return false;

		// Retrieve description of the texture surface so we can access its size
		D3DSURFACE_DESC my_image_desc;
		texture->GetLevelDesc(0, &my_image_desc);
		*out_texture = texture;
		*out_width = (int)my_image_desc.Width;
		*out_height = (int)my_image_desc.Height;
		return true;
	}
}