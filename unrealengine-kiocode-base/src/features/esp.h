#pragma once

#include "../includes.h"

class ESP
{
public:
	static ESP& GetInstance() {
		static ESP instance;
		return instance;
	}

	void RenderSkeleton(SDK::AREnemyPawnBase* pawn, ImColor color);
	void RenderSnapline(SDK::AREnemyPawnBase* pawn, ImColor color);
	void RenderBox(SDK::AREnemyPawnBase* pawn, ImColor color);
	void Render3DBox(SDK::AREnemyPawnBase* pawn, ImColor color);

private:

	ESP() = default;
	~ESP() = default;

	ESP(const ESP&) = delete;
	ESP& operator=(const ESP&) = delete;
};