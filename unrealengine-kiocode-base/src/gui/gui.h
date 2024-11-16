#pragma once

#include "../includes.h"

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

class GUI {
public:
	static GUI& GetInstance() {
		static GUI instance;
		return instance;
	}

	static HRESULT __stdcall hkPresentWrapper(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags) {
		return GetInstance().hkPresent(pSwapChain, SyncInterval, Flags);
	}

	static HRESULT __stdcall WndProcWrapper(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
		return GetInstance().WndProc(hWnd, uMsg, wParam, lParam);
	}

	Present oPresent;
	HRESULT __stdcall hkPresent(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags);
	LRESULT __stdcall WndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	void InitImGui();

private:

	HWND window = NULL;
	WNDPROC oWndProc;
	ID3D11Device* pDevice = NULL;
	ID3D11DeviceContext* pContext = NULL;
	ID3D11RenderTargetView* mainRenderTargetView;
	bool init = false;

	GUI() = default;
	~GUI() = default;

	GUI(const GUI&) = delete;
	GUI& operator=(const GUI&) = delete;
};