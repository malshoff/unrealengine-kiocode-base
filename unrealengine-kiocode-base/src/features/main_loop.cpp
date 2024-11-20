#include "main_loop.h"

#include "../config.h"
#include "../utils/validity.h"
#include "../utils/general.h"
#include "../utils/imgui/imgui_helper.h"

void MainLoop::DrawCrosshair() 
{
	ImColor color = Config::RainbowCrosshair ? Config::RainbowColor : Config::CrosshairColor;
	switch (Config::CrosshairType)
	{
	case 0:
		ImGui::GetForegroundDrawList()->AddLine(ImVec2(Config::System::ScreenCenter.x - Config::CrosshairSize, Config::System::ScreenCenter.y), ImVec2((Config::System::ScreenCenter.x - Config::CrosshairSize) + (Config::CrosshairSize * 2), Config::System::ScreenCenter.y), color, 1.2f);
		ImGui::GetForegroundDrawList()->AddLine(ImVec2(Config::System::ScreenCenter.x, Config::System::ScreenCenter.y - Config::CrosshairSize), ImVec2(Config::System::ScreenCenter.x, (Config::System::ScreenCenter.y - Config::CrosshairSize) + (Config::CrosshairSize * 2)), color, 1.2f);
		break;
	case 1:
		ImGui::GetForegroundDrawList()->AddCircle(ImVec2(Config::System::ScreenCenter.x, Config::System::ScreenCenter.y), Config::CrosshairSize, color, 100, 1.2f);
		break;
	}
}

void MainLoop::FetchFromObjects(std::vector<SDK::AActor*>* list)
{

	list->clear();

	for (int i = 0; i < SDK::UObject::GObjects->Num(); i++)
	{
		SDK::UObject* obj = SDK::UObject::GObjects->GetByIndex(i);

		if (!obj || obj->IsDefaultObject())
			continue;

		//if (!obj->IsA(SDK::APawn::StaticClass()) && !obj->HasTypeFlag(SDK::EClassCastFlags::Pawn))
		//    continue;
		
		// THIS PART CAN BE VARIABLE BELOW

		// Crabs Champions
		//if (!obj->IsA(SDK::ACrabEnemyC::StaticClass()))
		//	continue;
		
		// Destroy All Humans
		if (!obj->IsA(SDK::UBFGAnimationInstance_Human::StaticClass()))
			continue;

		SDK::UBFGAnimationInstance_Human* npc = static_cast<SDK::UBFGAnimationInstance_Human*>(obj);
		//npc->CurrentSkeleton
		if (!npc || !npc->GetVariables_Npc() ||
			Validity::IsBadPoint(npc) ||
			npc->GetVariables_Npc()->M_bDead || 
			npc->GetVariables_Npc()->M_bIsInCutscene ||
			npc->GetVariables_Human()->M_bDead || 
			npc->GetVariables_Human()->M_bIsInCutscene)
			continue;

		SDK::AActor* actor = npc->GetOwningActor();
		if (!actor || !actor->bCanBeDamaged)
			continue;

		//if (Config::MyController->GetSquaredDistanceTo(actor) > 5)
			//continue;

		list->push_back(actor);

	}
}

void MainLoop::FetchFromActors(std::vector<SDK::AActor*>* list)
{

	if (Config::World->Levels.Num() == 0)
		return;

	SDK::ULevel* currLevel = Config::World->Levels[0];
	if (!currLevel)
		return;

	list->clear();

	for (int j = 0; j < currLevel->Actors.Num(); j++)
	{
		SDK::AActor* currActor = currLevel->Actors[j];

		if (!currActor)
			continue;
		if (!currActor->RootComponent)
			continue;

		//const auto location = currActor->K2_GetActorLocation();
		//if (location.X == 0.f || location.Y == 0.f || location.Z == 0.f) continue;

		//if (currActor->GetFullName().find("YOUR_NPC") != std::string::npos)
		if (currActor->GetFullName().find("BP_Enemy") != std::string::npos)
		{
			list->push_back(currActor);
		}

	}
}

void MainLoop::FetchFromPlayers(std::vector<SDK::AActor*>* list)
{
	list->clear();

	SDK::TSubclassOf<SDK::ACharacter> PlayerBaseCharacterReference = SDK::ACharacter::StaticClass();
	SDK::TArray<SDK::AActor*> PlayerCharacters;
	SDK::UGameplayStatics::GetAllActorsOfClass(Config::World, PlayerBaseCharacterReference, &PlayerCharacters);

	for (SDK::AActor* actor : PlayerCharacters)
	{
		if (!actor || Validity::IsBadPoint(actor) || !actor->IsA(PlayerBaseCharacterReference)) continue;

		SDK::ACharacter* PlayerCharacter = reinterpret_cast<SDK::ACharacter*>(actor);
		if (!PlayerCharacter || !PlayerCharacter->PlayerState || !PlayerCharacter->PlayerState->GetPlayerName() || !PlayerCharacter->PlayerState->GetPlayerName().IsValid())
			continue;

		list->push_back(PlayerCharacter);
	}
}

void MainLoop::FetchEntities()
{
	while (true) {

		if (!Config::UpdateTargets)
		{
			std::lock_guard<std::mutex> lock(list_mutex);
			if (!Config::TargetsList.empty())
			{
				Config::TargetsList.clear();
			}

			Sleep(10);
			continue;
		}

		if (!Config::World || Validity::IsBadPoint(Config::World) || !Config::Engine || Validity::IsBadPoint(Config::Engine) || !Config::MyController || Validity::IsBadPoint(Config::MyController) || !Config::MyPawn || Validity::IsBadPoint(Config::MyPawn))
		{
			Sleep(10);
			continue;
		}

		if (!Config::World->GameState || Validity::IsBadPoint(Config::World->GameState) || Validity::IsBadPoint(Config::World->OwningGameInstance))
		{
			Sleep(10);
			continue;
		}

		std::vector<SDK::AActor*> newTargets;

		switch (Config::TargetFetch)
		{
		case 0:
			FetchFromObjects(&newTargets);
			break;

		case 1:
			FetchFromActors(&newTargets);
			break;

		case 2:
			FetchFromPlayers(&newTargets);
			break;
		}

		{
			std::lock_guard<std::mutex> lock(list_mutex);
			Config::TargetsList = std::move(newTargets);
		}

		Sleep(1);
	}
}

bool MainLoop::UpdateSDK() 
{
	Config::World = SDK::UWorld::GetWorld();
	if (Validity::IsBadPoint(Config::World)) 
	{
		std::cerr << "Error: World not found" << std::endl;
		return false;
	}
	//std::cout << "World address: 0x" << std::hex << reinterpret_cast<uintptr_t>(Config::World) << std::dec << std::endl;

	Config::Engine = SDK::UEngine::GetEngine();
	if (Validity::IsBadPoint(Config::Engine)) 
	{
		std::cerr << "Error: Engine not found" << std::endl;
		return false;
	}
	//std::cout << "Engine address: 0x" << std::hex << reinterpret_cast<uintptr_t>(Config::Engine) << std::dec << std::endl;

	// Init PlayerController
	if (Validity::IsBadPoint(Config::World->OwningGameInstance)) 
	{
		std::cerr << "Error: OwningGameInstance not found" << std::endl;
		return false;
	}
	if (Validity::IsBadPoint(Config::World->OwningGameInstance->LocalPlayers[0])) 
	{
		std::cerr << "Error: LocalPlayers[0] not found" << std::endl;
		return false;
	}
	Config::MyController = Config::World->OwningGameInstance->LocalPlayers[0]->PlayerController;
	if (Validity::IsBadPoint(Config::MyController)) 
	{
		std::cerr << "Error: MyController not found" << std::endl;
		return false;
	}
	//std::cout << "PlayerController address: 0x" << std::hex << reinterpret_cast<uintptr_t>(Config::MyController) << std::dec << std::endl;

	// Init Pawn
	Config::MyPawn = Config::MyController->AcknowledgedPawn;
	if (Config::MyPawn == nullptr) 
	{
		std::cerr << "Error: MyPawn not found" << std::endl;
		return false;
	}
	//std::cout << "MyPawn address: 0x" << std::hex << reinterpret_cast<uintptr_t>(Config::MyPawn) << std::dec << std::endl;

}

void MainLoop::Update(DWORD tick) 
{

	if (!UpdateSDK()) return;
	
	if (Config::GodMode) 
	{
		Config::MyController->SetLifeSpan(999);
	}

	if (Config::NoClip) 
	{
		Config::MyPawn->SetActorEnableCollision(false);
	}
	else if (!Config::NoClip && Config::MyPawn->GetActorEnableCollision()) 
	{
		Config::MyPawn->SetActorEnableCollision(true);
	}

	if (Config::CameraFovChanger) 
	{
		Config::MyController->FOV(Config::CameraCustomFOV);
	}

	if (Config::TimeScaleChanger) 
	{
		Config::World->K2_GetWorldSettings()->TimeDilation = Config::TimeScale;
	}

	std::shared_ptr<std::vector<SDK::AActor*>> currentTargets;

	{
		std::lock_guard<std::mutex> lock(list_mutex);
		currentTargets = std::make_shared<std::vector<SDK::AActor*>>(Config::TargetsList);
	}

	for (auto* currTarget : *currentTargets) 
	{

		if (!currTarget || Validity::IsBadPoint(currTarget) || currTarget == Config::MyController->GetOwner() || currTarget->GetLifeSpan() < 1)
			continue;

		if (Config::PlayerChams && Config::ChamsMaterial) 
		{
			SDK::ASkeletalMeshActor* mesh = reinterpret_cast<SDK::ASkeletalMeshActor*>(currTarget);
			Utility::ApplyChams(mesh->SkeletalMeshComponent, true);
		}

		if (Config::PlayersSnapline || Config::PlayersBox) 
		{
			SDK::FVector origin;
			SDK::FVector boxExtent;
			currTarget->GetActorBounds(true, &origin, &boxExtent);
			SDK::FVector footLocation = origin;
			SDK::FVector headLocation = origin;

			footLocation.Z -= boxExtent.Z * 0.15f;
			headLocation.Z += boxExtent.Z * 0.15f;

			SDK::FVector2D footPos;
			SDK::FVector2D headPos;
			if (!Config::MyController->ProjectWorldLocationToScreen(footLocation, &footPos, false))
				continue;
			if (!Config::MyController->ProjectWorldLocationToScreen(headLocation, &headPos, false))
				continue;

			if (Config::PlayersSnapline)
			{
				ImGui::GetBackgroundDrawList()->AddLine(ImVec2(Config::System::ScreenSize.x / 2, 0), ImVec2(footPos.X, footPos.Y), ImColor(255, 0, 0));
			}

			if (Config::PlayersBox) 
			{
				ImGui::GetBackgroundDrawList()->AddRect(ImVec2(footPos.X - boxExtent.X, footPos.Y - boxExtent.Y), ImVec2(footPos.X + boxExtent.X, footPos.Y + boxExtent.Y), ImColor(255, 0, 0));
				
				float distance = Config::MyController->GetDistanceTo(currTarget);
				ImGuiHelper::DrawOutlinedText(Config::GameFont, ImVec2(footPos.X, footPos.Y), 13.0f, ImColor(255, 255, 255), true, "%.1f", distance);
			}
		}
	}
}