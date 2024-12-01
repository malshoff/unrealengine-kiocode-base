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


LRESULT __stdcall GUI::WndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	if (Config::ShowMenu && ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam))
		return true;

	if (Config::ShowMenu)
		return true;

	return CallWindowProcA(oWndProc, hWnd, uMsg, wParam, lParam);
}

// main hook thread (it's a loop)
HRESULT __stdcall GUI::hkPresent(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags)
{
	if (!HkPresentInitialized)
	{
		if (SUCCEEDED(pSwapChain->GetDevice(__uuidof(ID3D11Device), (void**)&pDevice)))
		{
			pDevice->GetImmediateContext(&pContext);
			DXGI_SWAP_CHAIN_DESC sd;
			pSwapChain->GetDesc(&sd);
			window = sd.OutputWindow;
			ID3D11Texture2D* pBackBuffer = nullptr;
			pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
			pDevice->CreateRenderTargetView(pBackBuffer, NULL, &mainRenderTargetView);
			pBackBuffer->Release();
			oWndProc = (WNDPROC)SetWindowLongPtr(window, GWLP_WNDPROC, (LONG_PTR)WndProcWrapper);

			InitImGui();
			LoadFonts();

			HkPresentInitialized = true;
		}
		else return oPresent(pSwapChain, SyncInterval, Flags);
	}

	pContext->RSGetViewports(&Config::System::vps, &Config::System::Viewport);
	Config::System::ScreenSize = { Config::System::Viewport.Width, Config::System::Viewport.Height };
	Config::System::ScreenCenter = { Config::System::Viewport.Width / 2.0f, Config::System::Viewport.Height / 2.0f };

#pragma region Our context

	/*SDK::UMaterialInterface* material = SDK::UObject::FindObject<SDK::UMaterial>("Material WireframeMaterial.WireframeMaterial");
	if (!material) {
		std::cout << "Error: material not found" << std::endl;
	}
	else {
		Config::ChamsMaterial = SDK::UKismetMaterialLibrary::CreateDynamicMaterialInstance(Config::World, material, Utility::StrToName(L"ChamsVisibleMaterial"));
		if (!Config::ChamsMaterial) {
			std::cout << "Error: ChamsMaterial not found" << std::endl;
		} else {
			std::cout << "ChamsMaterial Found" << std::endl;
		}
	}*/

	DWORD currentTime = GetTickCount64();

	GetCursorPos(&Config::System::MousePos);
	ScreenToClient(window, &Config::System::MousePos);

	Core::GetInstance().HandleInputs();


	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	RenderUI();

	try { 
		MainLoop::GetInstance().Update(currentTime);
	} catch (const std::exception& e) {
		std::cout << e.what();
		MessageBoxA(NULL, e.what(), "Error", MB_OK | MB_ICONERROR);
	}

	ImGui::Render();


	if (currentTime - Config::LastTick > 5)
	{
		Config::LastTick = currentTime;
	}

#pragma endregion

	pContext->OMSetRenderTargets(1, &mainRenderTargetView, NULL);
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

	return oPresent(pSwapChain, SyncInterval, Flags);
}
