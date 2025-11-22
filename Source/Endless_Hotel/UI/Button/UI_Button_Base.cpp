// Copyright by 2025-2 WAP Game 2 team

#include "UI/Button/UI_Button_Base.h"

#pragma region Base

void UUI_Button_Base::ReleaseSlateResources(bool bReleaseChildren)
{
	GetWorld()->GetTimerManager().ClearAllTimersForObject(this);
}

#pragma endregion