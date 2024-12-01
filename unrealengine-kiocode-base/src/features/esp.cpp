#include "esp.h"

#include "../config.h"
#include "../utils/validity.h"

void ESP::RenderSkeleton(SDK::ACharacter* pawn, ImColor color)
{
	if (!pawn || !Config::MyController || Validity::IsBadPoint(Config::MyController) || Config::BonePairs.empty())
		return;

	SDK::USkeletalMeshComponent* mesh = pawn->Mesh;
	if (!mesh)
		return;

	for (const std::pair<int, int>& pair : Config::BonePairs)
	{
		const int bone1Index = pair.first;
		const int bone2Index = pair.second;

		const SDK::FVector boneLoc1 = pawn->Mesh->GetSocketLocation(pawn->Mesh->GetBoneName(bone1Index));
		const SDK::FVector boneLoc2 = pawn->Mesh->GetSocketLocation(pawn->Mesh->GetBoneName(bone2Index));

		SDK::FVector2D boneScreen;
		SDK::FVector2D prevBoneScreen;

		if (pawn == Config::CurrentTarget) color = Config::RainbowAimbotTargetColor ? Config::RainbowColor : Config::AimbotTargetColor;

		if (
			!Config::MyController->ProjectWorldLocationToScreen(boneLoc1, &boneScreen, false) ||
			!Config::MyController->ProjectWorldLocationToScreen(boneLoc2, &prevBoneScreen, false)
		) continue;


		ImGui::GetForegroundDrawList()->AddLine(
			ImVec2(boneScreen.X, boneScreen.Y),
			ImVec2(prevBoneScreen.X, prevBoneScreen.Y),
			color,
			1.0f
		);
	}
}

void ESP::RenderSnapline(SDK::ACharacter* pawn, ImColor color)
{
	if (!pawn || !Config::MyController || Validity::IsBadPoint(Config::MyController))
		return;

	SDK::FVector pawnLoc = pawn->K2_GetActorLocation();
	SDK::FVector2D pawnScreen;

	if (Config::MyController->ProjectWorldLocationToScreen(pawnLoc, &pawnScreen, false))
	{
		ImVec2 origin;

		switch (Config::PlayersSnaplineType) {
			case 0:
				origin = ImVec2(Config::System::ScreenCenter.x, 0);
				break;
			case 1:
				origin = ImVec2(Config::System::ScreenCenter.x, Config::System::ScreenCenter.y);
				break;
			case 2:
				origin = ImVec2(Config::System::ScreenCenter.x, Config::System::ScreenSize.y);
				break;
		}

		if (pawn == Config::CurrentTarget) color = Config::RainbowAimbotTargetColor ? Config::RainbowColor : Config::AimbotTargetColor;

		ImGui::GetBackgroundDrawList()->AddLine(
			origin,
			ImVec2(pawnScreen.X, pawnScreen.Y),
			color,
			1.0f
		);
	}
}	

void ESP::RenderBox(SDK::ACharacter* pawn, ImColor color)
{
	if (!pawn || !Config::MyController || Validity::IsBadPoint(Config::MyController) || Config::BonePairs.empty())
		return;

	SDK::USkeletalMeshComponent* mesh = pawn->Mesh;
	if (!mesh)
		return;

	SDK::FVector head = mesh->GetSocketLocation(mesh->GetBoneName(Config::BonePairs[4].second));
	SDK::FVector feet = mesh->GetSocketLocation(mesh->GetBoneName(Config::BonePairs[Config::BonePairs.size()-1].second));

	SDK::FVector2D headScreen;
	SDK::FVector2D feetScreen;

	if (
		!Config::MyController->ProjectWorldLocationToScreen(head, &headScreen, false) ||
		!Config::MyController->ProjectWorldLocationToScreen(feet, &feetScreen, false)
	) return;

	const float height = feetScreen.Y - headScreen.Y;
	const float width = height / 3;

	if (pawn == Config::CurrentTarget) color = Config::RainbowAimbotTargetColor ? Config::RainbowColor : Config::AimbotTargetColor;

	color.Value.w = 0.3f;

	// filled
	if (Config::PlayersBoxFilled) {
		ImGui::GetForegroundDrawList()->AddRectFilled(
			ImVec2(headScreen.X - width, headScreen.Y),
			ImVec2(headScreen.X + width, feetScreen.Y),
			color,
			0.0f,
			0
		);
	}

	color.Value.w = 1.0f;

	ImGui::GetForegroundDrawList()->AddRect(
		ImVec2(headScreen.X - width, headScreen.Y),
		ImVec2(headScreen.X + width, feetScreen.Y),
		color,
		0.0f,
		0,
		1.0f
	);
	
}

void ESP::Render3DBox(SDK::ACharacter* pawn, ImColor color)
{
	if (!pawn || !Config::MyController || Validity::IsBadPoint(Config::MyController) || Config::BonePairs.empty())
		return;

	SDK::USkeletalMeshComponent* mesh = pawn->Mesh;
	if (!mesh)
		return;

	SDK::FVector head = mesh->GetSocketLocation(mesh->GetBoneName(Config::BonePairs[4].second));
	SDK::FVector feet = mesh->GetSocketLocation(mesh->GetBoneName(Config::BonePairs[Config::BonePairs.size() - 1].second));

	SDK::FVector2D headScreen;
	SDK::FVector2D feetScreen;

	if (
		!Config::MyController->ProjectWorldLocationToScreen(head, &headScreen, false) ||
		!Config::MyController->ProjectWorldLocationToScreen(feet, &feetScreen, false)
	) return;

	if (pawn == Config::CurrentTarget) color = Config::RainbowAimbotTargetColor ? Config::RainbowColor : Config::AimbotTargetColor;

	SDK::FVector center = pawn->K2_GetActorLocation();
	const float height = feetScreen.Y - headScreen.Y;
	const float width = height / 3;
	const float depth = width;

	SDK::FVector corners[] = {
		{ center.X - width / 2, center.Y + depth / 2, center.Z - height / 2 }, // a1
		{ center.X + width / 2, center.Y + depth / 2, center.Z - height / 2 }, // a2
		{ center.X - width / 2, center.Y - depth / 2, center.Z - height / 2 }, // a3
		{ center.X + width / 2, center.Y - depth / 2, center.Z - height / 2 }, // a4
		{ center.X - width / 2, center.Y + depth / 2, center.Z + height / 2 }, // b1
		{ center.X + width / 2, center.Y + depth / 2, center.Z + height / 2 }, // b2
		{ center.X - width / 2, center.Y - depth / 2, center.Z + height / 2 }, // b3
		{ center.X + width / 2, center.Y - depth / 2, center.Z + height / 2 }  // b4
	};

	SDK::FVector2D screenCorners[8];
	bool isVisible = true;

	for (int i = 0; i < 8; i++) {
		if (!Config::MyController->ProjectWorldLocationToScreen(corners[i], &screenCorners[i], false)) {
			isVisible = false;
			break;
		}
	}

	if (isVisible) {
		ImVec2 s[8];
		for (int i = 0; i < 8; i++)
			s[i] = ImVec2(screenCorners[i].X, screenCorners[i].Y);

		ImGui::GetForegroundDrawList()->AddLine(s[0], s[1], color, 1.f);
		ImGui::GetForegroundDrawList()->AddLine(s[1], s[3], color, 1.f);
		ImGui::GetForegroundDrawList()->AddLine(s[3], s[2], color, 1.f);
		ImGui::GetForegroundDrawList()->AddLine(s[2], s[0], color, 1.f);

		ImGui::GetForegroundDrawList()->AddLine(s[4], s[5], color, 1.f);
		ImGui::GetForegroundDrawList()->AddLine(s[5], s[7], color, 1.f);
		ImGui::GetForegroundDrawList()->AddLine(s[7], s[6], color, 1.f);
		ImGui::GetForegroundDrawList()->AddLine(s[6], s[4], color, 1.f);

		ImGui::GetForegroundDrawList()->AddLine(s[0], s[4], color, 1.f);
		ImGui::GetForegroundDrawList()->AddLine(s[1], s[5], color, 1.f);
		ImGui::GetForegroundDrawList()->AddLine(s[2], s[6], color, 1.f);
		ImGui::GetForegroundDrawList()->AddLine(s[3], s[7], color, 1.f);
	}
}


