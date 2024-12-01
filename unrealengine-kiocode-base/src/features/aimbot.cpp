#include "aimbot.h"

#include "../config.h"
#include "../utils/general.h"

void Aimbot::RegularAimbot(SDK::ACharacter* pawn) 
{
	if (!pawn || !Config::MyController || Config::BonePairs.empty())
		return;

	SDK::USkeletalMeshComponent* mesh = pawn->Mesh;
	if (!mesh)
		return;

	SDK::FVector head = mesh->GetSocketLocation(mesh->GetBoneName(Config::BonePairs[4].second));

	SDK::FVector2D headScreen;

	if (
		!Config::MyController->ProjectWorldLocationToScreen(head, &headScreen, false)
	) return;

	if (Config::AimbotFOVCheck)
	{
		if (headScreen.X > (Config::System::ScreenCenter.x + Config::AimbotFOV))
			return;
		if (headScreen.X < (Config::System::ScreenCenter.x - Config::AimbotFOV))
			return;
		if (headScreen.Y > (Config::System::ScreenCenter.y + Config::AimbotFOV))
			return;
		if (headScreen.Y < (Config::System::ScreenCenter.y - Config::AimbotFOV))
			return;
	}

	if (GetAsyncKeyState(VK_RBUTTON)) 
	{
		if (Config::CurrentTarget == nullptr)
		{
			Config::CurrentTarget = pawn;
		}

		if (Config::CurrentTarget == pawn) 
		{
			Utility::MouseMove(headScreen.X, headScreen.Y, Config::System::ScreenSize.x, Config::System::ScreenSize.y, Config::AimbotSmoothness);
		}
	}
	else 
	{
		Config::CurrentTarget = nullptr;
	}
	

}