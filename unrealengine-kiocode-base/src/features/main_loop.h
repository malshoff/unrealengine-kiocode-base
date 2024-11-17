#pragma once

#include <vector>
#include <Windows.h>

#include "../includes.h"

class MainLoop
{
public:
	static MainLoop& GetInstance() {
		static MainLoop instance;
		return instance;
	}

	void DrawCrosshair();
	void FetchEntities();
	void FetchFromObjects(std::vector<SDK::AActor*>* list);
	void FetchFromActors(std::vector<SDK::AActor*>* list);
	void FetchFromPlayers(std::vector<SDK::AActor*>* list);
	void Update(DWORD tick);

private:

	MainLoop() = default;
	~MainLoop() = default;



	MainLoop(const MainLoop&) = delete;
	MainLoop& operator=(const MainLoop&) = delete;
};