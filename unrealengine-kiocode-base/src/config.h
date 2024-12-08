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
		inline static bool UpdateTargetsInDifferentThread = false; // some game is freezing (like OHD, OAR)
		inline static bool UpdateTargets = false;

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

	//inline static std::vector<SDK::AActor*> TargetsList{};
	inline static std::vector<SDK::ACharacter*> TargetsList{};
	inline static SDK::AActor* CurrentTarget;

	inline static ImColor TargetPlayerColor = ImColor(255, 0, 0);

	// dumped with Dumper::DumpUBones() 
	// OHD
	inline static std::vector<std::pair<int, int>> BonePairs = {
		// Spine
		{1, 2},  // pelvis -> spine_01
		{2, 3},  // spine_01 -> spine_02
		{3, 4},  // spine_02 -> spine_03
		{4, 47}, // spine_03 -> neck_01
		{47, 48}, // neck_01 -> head

		// Left arm
		{4, 5},   // spine_03 -> clavicle_l
		{5, 6},   // clavicle_l -> UpperArm_L
		{6, 7},   // UpperArm_L -> lowerarm_l
		{7, 8},   // lowerarm_l -> Hand_L
		{8, 9},   // Hand_L -> index_01_l
		{9, 10},  // index_01_l -> index_02_l
		{10, 11}, // index_02_l -> index_03_l
		{8, 12},  // Hand_L -> middle_01_l
		{12, 13}, // middle_01_l -> middle_02_l
		{13, 14}, // middle_02_l -> middle_03_l
		{8, 15},  // Hand_L -> pinky_01_l
		{15, 16}, // pinky_01_l -> pinky_02_l
		{16, 17}, // pinky_02_l -> pinky_03_l
		{8, 18},  // Hand_L -> ring_01_l
		{18, 19}, // ring_01_l -> ring_02_l
		{19, 20}, // ring_02_l -> ring_03_l
		{8, 21},  // Hand_L -> thumb_01_l
		{21, 22}, // thumb_01_l -> thumb_02_l
		{22, 23}, // thumb_02_l -> thumb_03_l

		// Right arm
		{4, 26},  // spine_03 -> clavicle_r
		{26, 27}, // clavicle_r -> UpperArm_R
		{27, 28}, // UpperArm_R -> lowerarm_r
		{28, 29}, // lowerarm_r -> Hand_R
		{29, 30}, // Hand_R -> index_01_r
		{30, 31}, // index_01_r -> index_02_r
		{31, 32}, // index_02_r -> index_03_r
		{29, 33}, // Hand_R -> middle_01_r
		{33, 34}, // middle_01_r -> middle_02_r
		{34, 35}, // middle_02_r -> middle_03_r
		{29, 36}, // Hand_R -> pinky_01_r
		{36, 37}, // pinky_01_r -> pinky_02_r
		{37, 38}, // pinky_02_r -> pinky_03_r
		{29, 39}, // Hand_R -> ring_01_r
		{39, 40}, // ring_01_r -> ring_02_r
		{40, 41}, // ring_02_r -> ring_03_r
		{29, 42}, // Hand_R -> thumb_01_r
		{42, 43}, // thumb_01_r -> thumb_02_r
		{43, 44}, // thumb_02_r -> thumb_03_r

		// Left leg
		{1, 49},  // pelvis -> Thigh_L
		{49, 50}, // Thigh_L -> calf_l
		{50, 52}, // calf_l -> Foot_L
		{52, 53}, // Foot_L -> ball_l

		// Right leg
		{1, 55},  // pelvis -> Thigh_R
		{55, 56}, // Thigh_R -> calf_r
		{56, 58}, // calf_r -> Foot_R
		{58, 59}  // Foot_R -> ball_r
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

	inline static bool KillAll = false;

	inline static bool RainbowAimbotTargetColor = false;
	inline static ImColor AimbotTargetColor = ImColor(255.0f / 255, 255.0f / 255, 255.0f / 255);

	inline static ImColor TargetNotVisibleColor = ImColor(255.0f / 255, 255.0f / 255, 255.0f / 255);
	inline static bool RainbowTargetNotVisibleColor = false;
	
	inline static bool PlayersBox3D = false;

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
	inline static float FakeHeadPosDiff = 2;
	inline static float FakeFeetPosDiff = 0;

};