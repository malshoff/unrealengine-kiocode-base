#pragma once

#include "includes.h"
#include "utils/vec2.h"

#define RAINBOW_BORDERS TRUE;

class Config 
{
public:

	class System
	{
	public:
		inline static constexpr const char* c_appName = "UnrealBase";
		inline static constexpr const char* c_author = "@kiocode";

		inline static bool Init = false;

		inline static POINT MousePos = { 0, 0 };

		inline static UINT vps = 1;
		inline static Vector2 ScreenSize = { 0, 0 };
		inline static Vector2 ScreenCenter = { 0, 0 };
		inline static D3D11_VIEWPORT Viewport;
	};

	class Keys
	{
	public:
		inline static int SHOWMENU_KEY = VK_INSERT;
		inline static int DEATTACH_KEY = VK_F9;
	};

	class Offsets // get it with https://github.com/Spuckwaffel/UEDumper maybe
	{
	public:
		//uintptr_t Health__TakeDamage_Offset = 0x0;
	};

	inline static ImFont* GameFont = NULL;

	inline static enum MenuTab
	{
		TAB_VISUALS,
		TAB_AIM,
		TAB_EXPLOITS,
		TAB_MISC,
		TAB_DEV
	};

	inline static int TargetFetch = 2;
	
	inline static SDK::UEngine* Engine;
	inline static SDK::UWorld* World;
	inline static SDK::APlayerController* MyController;
	inline static SDK::APawn* MyPawn;
	inline static SDK::ACharacter* MyCharacter;
	//inline static SDK::APlayerCharacter_C* CharacterClass;
	//inline static SDK::TArray<class SDK::APlayerState*> PlayerArray;

	inline static std::vector<SDK::AActor*> TargetsList;

	inline static ImColor TargetPlayerColor = ImColor(255, 0, 0);

	inline static std::vector<std::pair<int, int>> BonePairs = {
		// left foot
		{2, 1},
		{1, 0},
		{0, 3},
		// right foot
		{31, 30},
		{30, 20},
		{20, 3},
		// Spine
		{3, 4},
		// Right Hand
		{4, 9},
		// Left Hand
		{4, 7},
		// Neck
		{4, 5},
		// Head
		{5, 6},
	};

// Global rainbow color
	inline static ImVec4 Rainbow = ImVec4(0.0f, 0.0f, 0.0f, 0.0f); 
 // Global rainbow color
	inline static ImColor RainbowColor = ImColor(255.0f / 255, 255.0f / 255, 255.0f / 255); 

	inline static DWORD LastShotTime = 0;
	inline static DWORD LastTick = 0;

	inline static bool ShowMenu = false;
	inline static bool Watermark = false;

	inline static bool CameraFovChanger = false;
	inline static float CameraCustomFOV = 80.0f;

	inline static bool TimeScaleChanger = false;
	inline static float TimeScale = 1.0f;

	inline static bool EnableDeveloperOptions = false;

	inline static bool UpdateTargets = true;

	inline static bool ShowInspector = false;

	inline static bool ShowMouse = true;
	inline static bool RainbowMouse = false;
	inline static ImColor MouseColor = ImColor(255.0f / 255, 255.0f / 255, 255.0f / 255);
	inline static int MouseType = 0;

	inline static bool Fly = false;

	inline static bool NoGravity = false;

	inline static bool Crosshair = false;
	inline static bool RainbowCrosshair = false;
	inline static ImColor CrosshairColor = ImColor(255.0f / 255, 255.0f / 255, 255.0f / 255);
	inline static float CrosshairSize = 5.0f;
	inline static int CrosshairType = 0;

	inline static bool PlayersSnapline = false;
	inline static bool RainbowPlayersSnapline = false;
	inline static ImColor PlayersSnaplineColor = ImColor(255.0f / 255, 255.0f / 255, 255.0f / 255);
	inline static int PlayersSnaplineType = 2;

	inline static bool PlayerChams = false;
	inline static ImColor ChamsColorTargetVisible = ImColor(255.0f / 255, 255.0f / 255, 255.0f / 255);
	inline static ImColor ChamsColorTargetHidden = ImColor(255.0f / 255, 255.0f / 255, 255.0f / 255);
	inline static bool RainbowPlayerChams = false;
	inline static SDK::UMaterialInstanceDynamic* ChamsMaterial;

	inline static bool PlayerSkeleton = false;
	inline static bool RainbowPlayerSkeleton = false;
	inline static ImColor PlayerSkeletonColor = ImColor(255.0f / 255, 255.0f / 255, 255.0f / 255);

	inline static bool PlayersBox = false;
	inline static bool RainbowPlayersBox = false;
	inline static ImColor PlayersBoxColor = ImColor(255.0f / 255, 255.0f / 255, 255.0f / 255);
	inline static bool PlayersBoxFilled = false;

	inline static bool BotChecker = false;
	inline static bool RainbowBotChecker = false;
	inline static ImColor BotCheckerColor = ImColor(0, 0, 255);
	inline static bool BotCheckerText = true;

	inline static bool PlayersHealth = false;

	inline static bool GodMode = false;

	inline static bool NoRecoil = false;

	inline static bool NoSpread = false;

	inline static bool RapidFire = false;

	inline static bool OneShot = false;

	inline static bool InfiniteAmmo = false;
	
	inline static bool SpeedHack = false;
	inline static float SpeedValue = 1.0f;

	inline static bool NoClip = false;

	inline static bool EnableAimbot = false;
	inline static bool AimbotFOVCheck = false;
	inline static float AimbotFOV = 80.0f;
	inline static float AimbotSmoothness = 0.5f;
	inline static float FakeHeadPosDiff = 1;
	inline static float FakeFeetPosDiff = 1;

};