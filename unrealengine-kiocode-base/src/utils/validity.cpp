#include "validity.h"

namespace Validity {
	bool IsBadPoint(SDK::UEngine* ptr)
	{
		std::uintptr_t Pointer = reinterpret_cast<std::uintptr_t>(ptr);

		if ((Pointer < 0xFFFFFFFFFFULL) || (Pointer > 0x2FFFFFFFFFFULL))
			return true;

		return false;
	}

	bool IsBadPoint(SDK::UGameInstance* ptr)
	{
		std::uintptr_t Pointer = reinterpret_cast<std::uintptr_t>(ptr);

		if ((Pointer < 0xFFFFFFFFFFULL) || (Pointer > 0x2FFFFFFFFFFULL))
			return true;

		return false;
	}

	bool IsBadPoint(SDK::ULocalPlayer* ptr)
	{
		std::uintptr_t Pointer = reinterpret_cast<std::uintptr_t>(ptr);

		if ((Pointer < 0xFFFFFFFFFFULL) || (Pointer > 0x2FFFFFFFFFFULL))
			return true;

		return false;
	}

	bool IsBadPoint(SDK::APlayerController* ptr)
	{
		std::uintptr_t Pointer = reinterpret_cast<std::uintptr_t>(ptr);

		if ((Pointer < 0xFFFFFFFFFFULL) || (Pointer > 0x2FFFFFFFFFFULL))
			return true;

		return false;
	}

	bool IsBadPoint(SDK::APlayerState* ptr)
	{
		std::uintptr_t Pointer = reinterpret_cast<std::uintptr_t>(ptr);

		if ((Pointer < 0xFFFFFFFFFFULL) || (Pointer > 0x2FFFFFFFFFFULL))
			return true;

		return false;
	}

	bool IsBadPoint(SDK::UWorld* ptr)
	{
		std::uintptr_t Pointer = reinterpret_cast<std::uintptr_t>(ptr);

		if ((Pointer < 0xFFFFFFFFFFULL) || (Pointer > 0x2FFFFFFFFFFULL))
			return true;

		return false;
	}

	bool IsBadPoint(SDK::AGameStateBase* ptr)
	{
		std::uintptr_t Pointer = reinterpret_cast<std::uintptr_t>(ptr);

		if ((Pointer < 0xFFFFFFFFFFULL) || (Pointer > 0x2FFFFFFFFFFULL))
			return true;

		return false;
	}

	bool IsBadPoint(SDK::UProjectileMovementComponent* ptr)
	{
		std::uintptr_t Pointer = reinterpret_cast<std::uintptr_t>(ptr);

		if ((Pointer < 0xFFFFFFFFFFULL) || (Pointer > 0x2FFFFFFFFFFULL))
			return true;

		return false;
	}

	bool IsBadPoint(SDK::AActor* ptr)
	{
		std::uintptr_t Pointer = reinterpret_cast<std::uintptr_t>(ptr);

		if ((Pointer < 0xFFFFFFFFFFULL) || (Pointer > 0x2FFFFFFFFFFULL))
			return true;

		return false;
	}
}