// Copyright by 2025-2 WAP Game 2 team

#include "UI/PopUp/Loading/UI_PopUp_Loading.h"
#include "UI/Slider/Loading/UI_Slider_Loading.h"
#include "UI/Controller/UI_Controller.h"
#include "GameSystem/GameInstance/EHGameInstance.h"

#pragma region Base

void UUI_PopUp_Loading::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	auto* GameInstance = GetGameInstance<UEHGameInstance>();
	GameInstance->OpenLevel();

	auto* UICon = GameInstance->GetSubsystem<UUI_Controller>();
	UICon->CloseWidget();
}

#pragma endregion

#pragma region Loading

bool UUI_PopUp_Loading::IsLoadingComplete()
{
	return Slider_Loading->IsLoadingComplete();
}

#pragma endregion