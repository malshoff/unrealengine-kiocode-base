#include "core.h"

#include <iostream>
#include <Windows.h>

#include "../config.h"
#include "../features/main_loop.h"
#include "../utils/validity.h"
#include "../utils/general.h"
//#include "../lua/lua.h"
#include "../../libs/kiero/minhook/include/MinHook.h"

void Core::Setup()
{
	if (!Core::InitVars()) assert("Unable to finish the first setup");
	EnableHooks();
}

void Core::EnableHooks()
{
	// EXAMPLE
	//// Health__TakeDamage
	//if (MH_CreateHook(reinterpret_cast<LPVOID*>(
	//	Offsets::Health__TakeDamage_Offset),
	//	&HooksFunctions::Health__TakeDamage_hook,
	//	(LPVOID*)&HooksFunctions::Health__TakeDamage) == MH_OK)
	//{
	//	MH_EnableHook(reinterpret_cast<LPVOID*>(Offsets::Health__TakeDamage_Offset));
	//}
}

bool Core::InitVars() {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x03);
	std::cout << "\n*******************************************************************************" << std::endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN);
	std::cout << R"(  
     __  __     __     ______     ______     ______     _____     ______    
    /\ \/ /    /\ \   /\  __ \   /\  ___\   /\  __ \   /\  __-.  /\  ___\    
    \ \  _'-.  \ \ \  \ \ \/\ \  \ \ \____  \ \ \/\ \  \ \ \/\ \ \ \  __\   
     \ \_\ \_\  \ \_\  \ \_____\  \ \_____\  \ \_____\  \ \____-  \ \_____\    
      \/_/\/_/   \/_/   \/_____/   \/_____/   \/_____/   \/____/   \/_____/
    )" << std::endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x03);
	std::cout << "\n*******************************************************************************\n" << std::endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0F);

	return MainLoop::GetInstance().UpdateSDK(true);
}


void Core::HandleInputs() {
	if (GetAsyncKeyState(Config::Keys::SHOWMENU_KEY) & 1)
	{
		Config::ShowMenu = !Config::ShowMenu;
	}

	if (GetAsyncKeyState(Config::Keys::DEATTACH_KEY) & 1)
	{
		MH_DisableHook(MH_ALL_HOOKS);
		MH_Uninitialize();
		Config::ShowMenu = false;

		//if (LuaEditor::GetInstance().LuaState != NULL)
		//{
		//	lua_close(LuaEditor::GetInstance().LuaState);
		//}
	}
}


