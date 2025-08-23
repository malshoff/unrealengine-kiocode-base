#ifndef TEST_MODE

#include <thread>

#include "src/includes.h"
#include "src/gui/core/gui.h"
#include "src/utils/rainbow_calculator.hpp"
#include "src/features/core.h"
#include "src/utils/general.h"
#include "src/config.h"
#include "src/features/main_loop.h"


void StartBackgroundThreads()
{
	std::thread(RainbowCalculator::Update).detach();

	if(Config::System::m_bUpdateTargetsInDifferentThread) std::thread(&MainLoop::FetchEntities, &MainLoop::GetInstance()).detach();
	std::cout << "Background threads started." << std::endl;
}

void InitialSetup()
{
	Utility::CreateConsole();
	system("cls");

	Core::GetInstance().Setup();

	//LuaEditor::GetInstance().Init();

	// main loop
	kiero::bind(8, (void**)&GUI::GetInstance().oPresent, GUI::hkPresentWrapper);

	std::cout << "Kiero initialized successfully." << std::endl;
	StartBackgroundThreads();
}

DWORD WINAPI MainThread(LPVOID lpReserved)
{

	bool mainHkInitialized = false;
	do
	{
		if (kiero::init(kiero::RenderType::Auto) == kiero::Status::Success)
		{
			InitialSetup();
			mainHkInitialized = true;
		}
		else
		{
			MessageBoxA(NULL, "Kiero initialization failed", "Debug", MB_OK);
		}
	} while (!mainHkInitialized);
	std::cout << "Main thread started." << std::endl;
	return TRUE;
}

BOOL WINAPI DllMain(HMODULE hMod, DWORD dwReason, LPVOID lpReserved)
{

	switch (dwReason)
	{
	case DLL_PROCESS_ATTACH:
		DisableThreadLibraryCalls(hMod);
		CreateThread(nullptr, 0, MainThread, hMod, 0, nullptr);
		break;
	case DLL_PROCESS_DETACH:
		kiero::shutdown();
		break;
	}
	return TRUE;
}
#endif
