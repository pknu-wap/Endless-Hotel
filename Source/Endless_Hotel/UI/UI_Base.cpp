// Copyright by 2025-2 WAP Game 2 team

#include "UI/UI_Base.h"

#pragma region Base

void UUI_Base::NativeDestruct()
{
	GetWorld()->GetTimerManager().ClearAllTimersForObject(this);

	Super::NativeDestruct();
}

#pragma endregion