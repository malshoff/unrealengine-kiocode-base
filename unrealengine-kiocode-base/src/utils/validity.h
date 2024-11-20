#pragma once
#include "../includes.h"

namespace Validity {
    bool IsBadPoint(SDK::UEngine* ptr);
    bool IsBadPoint(SDK::UGameInstance* ptr);
    bool IsBadPoint(SDK::ULocalPlayer* ptr);
    bool IsBadPoint(SDK::APlayerController* ptr);
    bool IsBadPoint(SDK::APlayerState* ptr);
    bool IsBadPoint(SDK::UWorld* ptr);
    bool IsBadPoint(SDK::AGameStateBase* ptr);
    bool IsBadPoint(SDK::UProjectileMovementComponent* ptr);
    bool IsBadPoint(SDK::AActor* ptr);
    bool IsBadPoint(SDK::UBFGAnimationInstance_Human* ptr);
}