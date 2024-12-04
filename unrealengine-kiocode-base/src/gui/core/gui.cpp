#include "gui.h"

#include "../modmenu.h"
#include "../../config.h"
#include "../../includes.h"
#include "../../features/core.h"
#include "../../features/main_loop.h"
#include "../../utils/general.h"
#include "../../utils/imgui/fonts/font.h"
#include "../../utils/imgui/imgui_helper.h"

void GUI::InitImGui()
{
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags = ImGuiConfigFlags_NoMouseCursorChange;
	ImGui_ImplWin32_Init(window);
	ImGui_ImplDX11_Init(pDevice, pContext);
}

void GUI::LoadFonts() 
{
	ImGui::GetIO().Fonts->AddFontDefault();
	ImFontConfig font_cfg;
	font_cfg.GlyphExtraSpacing.x = 1.2;
	Config::GameFont = ImGui::GetIO().Fonts->AddFontFromMemoryTTF(TTSquaresCondensedBold, 14, 14, &font_cfg);
}

void GUI::RenderMouse() 
{
	if (!Config::ShowMouse) return;

	ImColor color = Config::RainbowMouse ? Config::RainbowColor : Config::MouseColor;

	switch (Config::MouseType) {
	case 0:
		ImGui::GetForegroundDrawList()->AddCircleFilled(ImGui::GetMousePos(), 4, color);
		break;
	case 1:
		ImGuiHelper::DrawOutlinedTextForeground(Config::GameFont, ImVec2(Config::System::MousePos.x, Config::System::MousePos.y), 13.0f, color, false, "X");
		break;
	case 2:
		if (!ImGui::GetIO().MouseDrawCursor) {
			ImGui::GetIO().MouseDrawCursor = true;
		}
		break;
	}
}

void GUI::RenderUI() 
{

	if (Config::ShowMenu)
	{
		RenderMouse();

		// our menu
		ModMenu::Window();
	}

	if (Config::Watermark)
	{
		ImGuiHelper::DrawOutlinedText(Config::GameFont, ImVec2(Config::System::ScreenCenter.x, Config::System::ScreenSize.y - 20), 13.0f, Config::RainbowColor, true, Config::System::c_author);
		ImGuiHelper::DrawOutlinedText(Config::GameFont, ImVec2(Config::System::ScreenCenter.x, 5), 13.0f, Config::RainbowColor, true, "[ %.1f FPS ]", ImGui::GetIO().Framerate);
	}

	if (Config::Crosshair) {
		MainLoop::GetInstance().DrawCrosshair();
	}

	if (Config::AimbotFOVCheck) {
		ImGui::GetForegroundDrawList()->AddCircle(ImVec2(Config::System::ScreenCenter.x, Config::System::ScreenCenter.y), Config::AimbotFOV, ImColor(255, 255, 255), 360);
	}

}

