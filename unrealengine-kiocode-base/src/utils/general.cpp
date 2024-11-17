#include "general.h"

#include <iostream>
#include <Windows.h>

#include "../config.h"

namespace Utility
{
	void CreateConsole() 
	{
		AllocConsole();
		AttachConsole(GetCurrentProcessId());
		SetConsoleTitle(Config::System::c_author);
		FILE* f;
		freopen_s(&f, "CONOUT$", "w", stdout);
	}

	void MouseMove(float tarx, float tary, float X, float Y, int smooth)
	{
		float ScreenCenterX = (X / 2);
		float ScreenCenterY = (Y / 2);
		float TargetX = 0;
		float TargetY = 0;

		smooth = smooth + 3;

		if (tarx != 0)
		{
			if (tarx > ScreenCenterX)
			{
				TargetX = -(ScreenCenterX - tarx);
				TargetX /= smooth;
				if (TargetX + ScreenCenterX > ScreenCenterX * 2) TargetX = 0;
			}

			if (tarx < ScreenCenterX)
			{
				TargetX = tarx - ScreenCenterX;
				TargetX /= smooth;
				if (TargetX + ScreenCenterX < 0) TargetX = 0;
			}
		}

		if (tary != 0)
		{
			if (tary > ScreenCenterY)
			{
				TargetY = -(ScreenCenterY - tary);
				TargetY /= smooth;
				if (TargetY + ScreenCenterY > ScreenCenterY * 2) TargetY = 0;
			}

			if (tary < ScreenCenterY)
			{
				TargetY = tary - ScreenCenterY;
				TargetY /= smooth;
				if (TargetY + ScreenCenterY < 0) TargetY = 0;
			}
		}
		mouse_event(MOUSEEVENTF_MOVE, static_cast<DWORD>(TargetX), static_cast<DWORD>(TargetY), NULL, NULL);
	}

	void Log(uintptr_t address, const char* className, const char* methodName) {
		std::cout << "[ LOG ] " << className << "$$" << methodName << ": " << address << "\n" << std::endl;
	}

	void LogError(const char* text, const char* name) {
		std::cout << "[ LOG ]  " << text << ":  " << name << "\n" << std::endl;
	}
}