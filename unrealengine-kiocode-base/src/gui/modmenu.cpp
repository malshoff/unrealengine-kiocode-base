#include "modmenu.h"

#include "../includes.h"
#include "../config.h"
#include "../utils/dumper.h"
//#include "../lua/lua.h"
#include "themes.h"

void ModMenu::Window() {

	Themes::ImGuiThemeKio();

	//if (LuaEditor::GetInstance().ShowEditor) {
	//	LuaEditor::GetInstance().RenderLuaEditor();
	//}

	if (ImGui::Begin(Config::System::c_author, nullptr, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoSavedSettings))
	{
		ImGui::SetWindowPos(ImVec2(500, 500), ImGuiCond_Once);
		ImGui::SetWindowSize(ImVec2(600, 300), ImGuiCond_Once);
		static Config::MenuTab tabIndex = Config::TAB_VISUALS;
		ImGui::SameLine();
		if (ImGui::Button("Visual"))
		{
			tabIndex = Config::TAB_VISUALS;
		}
		ImGui::SameLine();
		if (ImGui::Button("Aim"))
		{
			tabIndex = Config::TAB_AIM;
		}
		ImGui::SameLine();
		if (ImGui::Button("Exploits"))
		{
			tabIndex = Config::TAB_EXPLOITS;
		}
		ImGui::SameLine();
		if (ImGui::Button("Misc"))
		{
			tabIndex = Config::TAB_MISC;
		}
		ImGui::SameLine();
		if (ImGui::Button("Developer"))
		{
			tabIndex = Config::TAB_DEV;
		}
		ImGui::Separator();
		ImGui::Spacing();
		switch (tabIndex) {
			case Config::TAB_VISUALS: {

				{ // ESP
					ImGui::Checkbox("Players Snapline", &Config::PlayersSnapline);
					ImGui::SameLine();
					ImGui::ColorEdit3("##PlayersSnaplineColor", (float*)&Config::PlayersSnaplineColor, ImGuiColorEditFlags_NoDragDrop | ImGuiColorEditFlags_NoInputs);
					if (ImGui::IsItemHovered()) ImGui::SetTooltip("Color of the players snapline");
					ImGui::SameLine();
					ImGui::Checkbox("##RGB3", &Config::RainbowPlayersSnapline);
					if (ImGui::IsItemHovered()) ImGui::SetTooltip("Toggle rainbow color on the players snapline");
					ImGui::Text("Snapline Type");
					ImGui::SameLine();
					ImGui::SliderInt("##PlayersSnaplineType", &Config::PlayersSnaplineType, 0, 2);
				}

				{ // bot checker
					ImGui::Checkbox("Bot Checker", &Config::BotChecker);
					ImGui::SameLine();
					ImGui::ColorEdit3("##BotCheckerColor", (float*)&Config::BotCheckerColor, ImGuiColorEditFlags_NoDragDrop | ImGuiColorEditFlags_NoInputs);
					if (ImGui::IsItemHovered()) ImGui::SetTooltip("Color of the bot checker");
					ImGui::SameLine();
					ImGui::Checkbox("##RGB4", &Config::RainbowBotChecker);
					if (ImGui::IsItemHovered()) ImGui::SetTooltip("Toggle rainbow color on the bot checker");
					ImGui::SameLine();
					ImGui::Checkbox("Show Bot Text", &Config::BotCheckerText);
					if (ImGui::IsItemHovered()) ImGui::SetTooltip("Show text 'Bot' on the bot checker");
				}

				{ // Players Box
					ImGui::Checkbox("Players Box", &Config::PlayersBox);
					ImGui::SameLine();
					ImGui::ColorEdit3("##PlayersBoxColor", (float*)&Config::PlayersBoxColor, ImGuiColorEditFlags_NoDragDrop | ImGuiColorEditFlags_NoInputs);
					if (ImGui::IsItemHovered()) ImGui::SetTooltip("Color of the players box");
					ImGui::SameLine();
					ImGui::Checkbox("##RGB5", &Config::RainbowPlayersBox);
					if (ImGui::IsItemHovered()) ImGui::SetTooltip("Toggle rainbow color on the players box");
					ImGui::SameLine();
					ImGui::Checkbox("##Filled", &Config::PlayersBoxFilled);
					if (ImGui::IsItemHovered()) ImGui::SetTooltip("Fill the players box");
				}

				{ // Player Skeleton
					ImGui::Checkbox("Players Skeleton", &Config::PlayerSkeleton);
					ImGui::SameLine();
					ImGui::ColorEdit3("##PlayerSkeletonColor", (float*)&Config::PlayerSkeletonColor, ImGuiColorEditFlags_NoDragDrop | ImGuiColorEditFlags_NoInputs);
					if (ImGui::IsItemHovered()) ImGui::SetTooltip("Color of the players skeleton");
					ImGui::SameLine();
					ImGui::Checkbox("##RGB6", &Config::RainbowPlayerSkeleton);
					if (ImGui::IsItemHovered()) ImGui::SetTooltip("Toggle rainbow color on the players skeleton");
				}

				{ // Charms
					ImGui::Checkbox("Players Chams", &Config::PlayerChams);
				}

				/* { // Players Health
					ImGui::Checkbox("Players Health", &Config::PlayersHealth);
				}*/

				/*if(ImGui::Button("UnlockAll")) {
					Config::UnlockAll = true;
				}*/


				break;
			}
			case Config::TAB_AIM: {

				{ // Aimbot
					ImGui::Text("Aimbot Height");
					ImGui::Text("Head Diff Pos");
					ImGui::SameLine();
					ImGui::SliderFloat("##Head Pos", &Config::FakeHeadPosDiff, -10.0f, 30.0f);
					ImGui::Text("Feet Diff Pos");
					ImGui::SameLine();
					ImGui::SliderFloat("##Feet Pos", &Config::FakeFeetPosDiff, -10.0f, 30.0f);

					ImGui::Separator();
					ImGui::Spacing();

					ImGui::Checkbox("Enable Aimbot", &Config::EnableAimbot);
					ImGui::Checkbox("Aimbot FOV Check", &Config::AimbotFOVCheck);
					ImGui::Text("Aimbot FOV");
					ImGui::SameLine();
					ImGui::SliderFloat("##Aimbot FOV", &Config::AimbotFOV, 0.1f, 800.0f);
					ImGui::Text("Aimbot Smoothness");
					ImGui::SameLine();
					ImGui::SliderFloat("##Aimbot Smooth", &Config::AimbotSmoothness, 0.0f, 30.0f);

				}
				break;
			}
			case Config::TAB_EXPLOITS: {

				{ // GodMode
					ImGui::Checkbox("GodMode", &Config::GodMode);
				}
				
				{ // NoClip
					ImGui::Checkbox("NoClip", &Config::NoClip);
				}

				{ // Time Scale
					ImGui::Checkbox("Time Dilation", &Config::TimeScaleChanger);
					ImGui::Text("Time Dilation Value");
					ImGui::SameLine();
					ImGui::SliderFloat("##TimeDilation", &Config::TimeScale, 0.1f, 1000.0f);
				}

				/* 
				{ // No Recoil
					ImGui::Checkbox("No Recoil", &Config::NoRecoil);
				}

				{ // No Spread
					ImGui::Checkbox("No Spread", &Config::NoSpread);
				}

				{ // One Hit Kill
					ImGui::Checkbox("One Hit Kill", &Config::OneShot);
				}

				{ // Rapid Fire
					ImGui::Checkbox("Rapid Fire", &Config::RapidFire);
				}

				{ // Infinite Ammo
					ImGui::Checkbox("Infinite Ammo", &Config::InfiniteAmmo);
				}

				{ // Speed Hack
					ImGui::Checkbox("Speed Hack", &Config::SpeedHack);
					ImGui::Text("Speed Value");
					ImGui::SameLine();
					ImGui::SliderFloat("##Speed", &Config::SpeedValue, 0.1f, 1000.0f);
				}*/
				break;
			}
			case Config::TAB_MISC: {

				{ // Render Things
					ImGui::Checkbox("Show Watermark", &Config::Watermark);
				}

				{ // Mouse things
					ImGui::Checkbox("Draw mouse", &Config::ShowMouse);
					ImGui::SameLine();
					ImGui::ColorEdit3("##MouseColor", (float*)&Config::MouseColor, ImGuiColorEditFlags_NoDragDrop | ImGuiColorEditFlags_NoInputs);
					if (ImGui::IsItemHovered()) ImGui::SetTooltip("Color of the mouse");
					ImGui::SameLine();
					ImGui::Checkbox("##RGB1", &Config::RainbowMouse);
					if (ImGui::IsItemHovered()) ImGui::SetTooltip("Toggle rainbow color on the mouse");
					ImGui::Text("Mouse Type");
					ImGui::SameLine();
					ImGui::SliderInt("##Mouse type", &Config::MouseType, 0, 1);
				}

				{ // Crosshair
					ImGui::Checkbox("Crosshair", &Config::Crosshair);
					ImGui::SameLine();
					ImGui::ColorEdit3("##CrosshairColor", (float*)&Config::CrosshairColor, ImGuiColorEditFlags_NoDragDrop | ImGuiColorEditFlags_NoInputs);
					if (ImGui::IsItemHovered()) ImGui::SetTooltip("Color of the crosshair");
					ImGui::SameLine();
					ImGui::Checkbox("##RGB2", &Config::RainbowCrosshair);
					if (ImGui::IsItemHovered()) ImGui::SetTooltip("Toggle rainbow color on the crosshair");
					ImGui::Text("Crosshair Size");
					ImGui::SameLine();
					ImGui::SliderFloat("##Crosshair Size", &Config::CrosshairSize, 0.1f, 10.0f);
					ImGui::Text("Crosshair Type");
					ImGui::SameLine();
					ImGui::SliderInt("##Crosshair type", &Config::CrosshairType, 0, 1);
				}

				{ // Camera fov
					ImGui::Checkbox("Camera Fov Changer", &Config::CameraFovChanger);
					ImGui::Text("Camera Custom FOV");
					ImGui::SameLine();
					ImGui::SliderFloat("##Camera Custom FOV", &Config::CameraCustomFOV, 0.1f, 300.0f);
				}

				break;
			}
			case Config::TAB_DEV: {

				ImGui::Checkbox("Enable Developer Options", &Config::EnableDeveloperOptions);

				if (Config::EnableDeveloperOptions)
				{
					ImGui::Indent();

					char aBufEngineOffset[256];
					sprintf_s(aBufEngineOffset, sizeof(aBufEngineOffset), "Engine Address: %#xh", reinterpret_cast<uintptr_t>(Config::Engine));
					ImGui::Text(aBufEngineOffset);

					char aBufWorldOffset[256];
					sprintf_s(aBufWorldOffset, sizeof(aBufWorldOffset), "World Address: %#xh", reinterpret_cast<uintptr_t>(Config::World));
					ImGui::Text(aBufWorldOffset);

					ImGui::Spacing();

					ImGui::Checkbox("Update Targets", &Config::UpdateTargets);

					char aBufTargets[256];
					sprintf_s(aBufTargets, sizeof(aBufTargets), "Targets: %zu", Config::TargetsList.size());
					ImGui::Text(aBufTargets);

					// fetch type: 0 = objects, 1 = actors, 2 = players
					char aBufFetchType[256];
					sprintf_s(aBufFetchType, sizeof(aBufFetchType), "Fetch Type: %s", Config::TargetFetch == 0 ? "Objects" : Config::TargetFetch == 1 ? "Actors" : "Players");
					ImGui::Text(aBufFetchType);

					ImGui::SliderInt("##FetchType", &Config::TargetFetch, 0, 2);

					ImGui::Spacing();

					if (ImGui::Button("Dump scene actors")) {
						Dumper::DumpUObjects();
					}

					if (ImGui::Button("Dump scene objects")) {
						Dumper::DumpUObjects();
					}

					//ImGui::Checkbox("Show Lua Editor", &Lua::ShowEditor);
					ImGui::Spacing();

					ImGui::Unindent();

				}
				break;
			}
		}
		ImGui::End();

	}
}
