#pragma once

#include <Windows.h>

namespace Utility 
{
	void CreateConsole();
	void MouseMove(float tarx, float tary, float X, float Y, int smooth);
	void Log(uintptr_t address, const char* className, const char* methodName);
	void LogError(const char* text, const char* name);
}