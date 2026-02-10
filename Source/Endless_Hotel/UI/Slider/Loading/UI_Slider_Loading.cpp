// Copyright by 2025-2 WAP Game 2 team

#include "UI/Slider/Loading/UI_Slider_Loading.h"
#include "GameSystem/GameInstance/EHGameInstance.h"

#pragma region Base

void UUI_Slider_Loading::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	SetLoadingPercentage();
}

#pragma endregion

#pragma region Loading

void UUI_Slider_Loading::SetLoadingPercentage()
{
	auto* GameInstance = GetWorld()->GetGameInstance<UEHGameInstance>();
	float Value = GameInstance->GetMapLoadingPercentage();

	Slide_Slider(Value);
}

#pragma endregion