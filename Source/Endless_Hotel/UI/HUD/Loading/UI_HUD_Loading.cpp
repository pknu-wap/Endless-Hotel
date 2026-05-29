// Copyright by 2025-2 WAP Game 2 team

#include "UI/HUD/Loading/UI_HUD_Loading.h"
#include "UI/Slider/Loading/UI_Slider_Loading.h"
#include "UI/Controller/UI_Controller.h"
#include "GameSystem/GameInstance/EHGameInstance.h"

#pragma region Show

void UUI_HUD_Loading::ShowWidget()
{
	Super::ShowWidget();
	
	Slider_Loading->ResetLoadingPercentage();

	GetWorld()->GetTimerManager().SetTimer(WaitHandle, this, &ThisClass::WaitForLoading, 0.01f, true);
}

#pragma endregion

#pragma region Loading

void UUI_HUD_Loading::WaitForLoading()
{
	if (Slider_Loading->IsLoadingComplete())
	{
		GetWorld()->GetTimerManager().ClearTimer(WaitHandle);

		auto* GameInstance = GetGameInstance<UEHGameInstance>();
		GameInstance->OpenLevel();

		auto* UICon = GameInstance->GetSubsystem<UUI_Controller>();
		UICon->CloseWidget();
	}
}

#pragma endregion