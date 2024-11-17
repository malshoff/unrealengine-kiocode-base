#include "main_loop.h"

#include "../config.h"
#include "../utils/validity.h"

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
		SDK::UObject* Obj = SDK::UObject::GObjects->GetByIndex(i);

		if (!Obj || Obj->IsDefaultObject())
			continue;

		//if (!Obj->IsA(SDK::APawn::StaticClass()) && !Obj->HasTypeFlag(SDK::EClassCastFlags::Pawn))
		//    continue;
		
		// THIS PART CAN BE VARIABLE BELOW

		// Crabs Champions
		//if (!Obj->IsA(SDK::ACrabEnemyC::StaticClass()))
		//	continue;
		
		// Destroy All Humans
		if (!Obj->IsA(SDK::UBFGAnimationInstance_Human::StaticClass()))
			continue;

		SDK::UBFGAnimationInstance_Human* npc = static_cast<SDK::UBFGAnimationInstance_Human*>(Obj);
		SDK::AActor* actor = npc->GetOwningActor();

		if (!npc || npc->GetVariables_Npc()->M_bDead || !actor)
			continue;

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

	for (SDK::AActor* Actor : PlayerCharacters)
	{
		if (!Actor || !Actor->IsA(SDK::ACharacter::StaticClass())) continue;

		SDK::ACharacter* PlayerCharacter = reinterpret_cast<SDK::ACharacter*>(Actor);
		if (!PlayerCharacter || !PlayerCharacter->PlayerState || !PlayerCharacter->PlayerState->GetPlayerName().IsValid()) continue;

		list->push_back(PlayerCharacter);
	}
}

void MainLoop::FetchEntities()
{
	switch (Config::TargetFetch) {

		case 0:
			FetchFromObjects(&Config::TargetsList);
			break;

		case 1:
			FetchFromActors(&Config::TargetsList);
			break;

		case 2:
			FetchFromPlayers(&Config::TargetsList);
			break;
	}
}	

void MainLoop::Update(DWORD tick) 
{
	if (!Config::World || !Config::Engine) return;

	if (Config::UpdateTargets) {
		FetchEntities();
	}
	else if (!Config::UpdateTargets && Config::TargetsList.size() > 0) {
		Config::TargetsList.clear();
	}

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

	for (int i = 0; i < Config::TargetsList.size(); i++)
	{
		SDK::AActor* currTarget = Config::TargetsList[i];

		if (!currTarget)
			continue;

		SDK::FVector origin;
		SDK::FVector boxExtent;
		currTarget->GetActorBounds(true, &origin, &boxExtent);
		SDK::FVector footLocation = origin;
		SDK::FVector headLocation = origin;

		footLocation.Z -= boxExtent.Z * 0.15f;
		headLocation.Z += boxExtent.Z * 0.15f;

		SDK::FVector2D footPos{};
		SDK::FVector2D headPos{};
		if (!Config::MyController->ProjectWorldLocationToScreen(footLocation, &footPos, false))
			continue;
		if (!Config::MyController->ProjectWorldLocationToScreen(headLocation, &headPos, false))
			continue;

		if (Config::PlayersSnapline) 
		{
			ImGui::GetBackgroundDrawList()->AddLine(ImVec2(Config::System::ScreenSize.x / 2, 0), ImVec2(footPos.X, footPos.Y), ImColor(255, 0, 0));
		}
	}
}