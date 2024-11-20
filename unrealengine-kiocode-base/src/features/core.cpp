#include "core.h"

#include <iostream>
#include <Windows.h>

#include "../config.h"
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

	// GET WORLD AND ENGINE
	Config::World = SDK::UWorld::GetWorld();
	if (Validity::IsBadPoint(Config::World)) {
		std::cerr << "Error: World not found" << std::endl;
		return false;
	}
	std::cout << "World address: 0x" << std::hex << reinterpret_cast<uintptr_t>(Config::World) << std::dec << std::endl;

	Config::Engine = SDK::UEngine::GetEngine();
	if (Validity::IsBadPoint(Config::Engine)) {
		std::cerr << "Error: Engine not found" << std::endl;
		return false;
	}
	std::cout << "Engine address: 0x" << std::hex << reinterpret_cast<uintptr_t>(Config::Engine) << std::dec << std::endl;

	// Init PlayerController
	if (Validity::IsBadPoint(Config::World->OwningGameInstance)) {
		std::cerr << "Error: OwningGameInstance not found" << std::endl;
		return false;
	}
	if (Validity::IsBadPoint(Config::World->OwningGameInstance->LocalPlayers[0])) {
		std::cerr << "Error: LocalPlayers[0] not found" << std::endl;
		return false;
	}
	Config::MyController = Config::World->OwningGameInstance->LocalPlayers[0]->PlayerController;
	if (Validity::IsBadPoint(Config::MyController)) {
		std::cerr << "Error: MyController not found" << std::endl;
		return false;
	}
	std::cout << "PlayerController address: 0x" << std::hex << reinterpret_cast<uintptr_t>(Config::MyController) << std::dec << std::endl;
	
	// Init Pawn
	Config::MyPawn = Config::MyController->AcknowledgedPawn;
	if (Config::MyPawn == nullptr) {
		std::cerr << "Error: MyPawn not found" << std::endl;
		return false;
	}
	std::cout << "MyPawn address: 0x" << std::hex << reinterpret_cast<uintptr_t>(Config::MyPawn) << std::dec << std::endl;

	/*SDK::UMaterialInterface* material = SDK::UObject::FindObject<SDK::UMaterial>("Material WireframeMaterial.WireframeMaterial");
	if (!material) {
		std::cerr << "Error: material not found" << std::endl;
		return false;
	}
	Config::ChamsMaterial = SDK::UKismetMaterialLibrary::CreateDynamicMaterialInstance(Config::World, material, Utility::StrToName(L"ChamsVisibleMaterial"));
	if (!Config::ChamsMaterial) {
		std::cout << "Error: ChamsMaterial not found" << std::endl;
	} else {
		std::cout << "ChamsMaterial Found" << std::endl;
	}*/

	return true;
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


