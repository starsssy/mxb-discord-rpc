#pragma once

#include <Windows.h>
#include <string>
#include <array>
#include <vector>
#include <iostream>
#include <thread>
#include <psapi.h>
#include <intrin.h>
#include <fstream>

#define CONSOLE
#ifdef CONSOLE
#define DbgMsg printf
#else
#define DbgMsg(msg)
#endif

#define MXB_EXPORT extern "C" _declspec(dllexport)

#include "tinyformat.h"

// FOR THE LIB: NEEDS DISCORD DLL IN EXE DIRECTORY
#include "discord/src/discord.h" // https://dl-game-sdk.discordapp.net/3.2.1/discord_game_sdk.zip // https://discord.com/developers/docs/developer-tools/game-sdk#using-the-sdk

#include "structs.h"
#include "rpc.h"