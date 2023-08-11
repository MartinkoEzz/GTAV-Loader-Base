#pragma once
#include <unordered_map>
#include "Utility/Obfuscate.hpp"
#include <thread>
#include <fstream>
// HOW TO USE
// g_Name = The name of your epic mod menu!
// g_DiscordURL = The url of your discord server
// g_KillswitchPaste = A raw pastebin containg YES or NO, if it's set to YES the launcher won't open
// g_KeyPaste = The pastebin of your key, make sure to change this every 2-3 days with a new key, do **NOT** add text to it only add the key like I did
// g_LinkvertiseURL = The linkvertise redirect to your key pastebin
// g_DllUrl = Download link of your dll, can be a discord url or a self hosted one like github, replit for auto-update.

// OBFUSCATE to all strings, this is due to you not using a packer, and we can't have people steal some stuff here so make sure to use OBFUSCATE when using strings or chars

// BASE HAS BEEN ORIGINALLY MADE BY STASH, I JUST FIXED IT AND MADE IT BETTER!!!

inline bool g_Running = true;
inline bool g_Authed = true;
inline bool g_Resources_Downloaded = false;
inline char g_Key[55] = "";
inline std::string g_Name = OBFUSCATE("GTAV Loader Base");
inline std::string g_DiscordURL = OBFUSCATE("https://discord.com");
inline std::string g_KillswitchPaste = OBFUSCATE("https://pastebin.com");
inline std::string g_KeyPaste = OBFUSCATE("https://pastebin.com");
inline std::string g_LinkvertiseURL = OBFUSCATE("https://linkvertise.com/"); // Make this your linkvertise url, make it a redirect to g_KeyPaste
inline std::string g_DllUrl = OBFUSCATE("https://cdn.discordapp.com/attachments/1131619784539263097/1139564436449923154/Nerox.dll");; // I just put Nerox as i got DLL ready.