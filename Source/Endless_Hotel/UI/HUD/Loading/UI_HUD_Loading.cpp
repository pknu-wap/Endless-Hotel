// Copyright by 2025-2 WAP Game 2 team

#include "UI/HUD/Loading/UI_HUD_Loading.h"
#include "UI/HUD/Title/UI_HUD_Title.h"
#include "UI/Slider/Loading/UI_Slider_Loading.h"
#include "UI/Controller/UI_Controller.h"

#pragma region Show

void UUI_HUD_Loading::ShowWidget()
{
	Super::ShowWidget();
	
	Slider_Loading->ResetLoadingPercentage();

	auto* UICon = GetGameInstance()->GetSubsystem<UUI_Controller>();
	auto* UI_Title = Cast<UUI_HUD_Title>(UICon->GetCachedWidget(EWidgetType::HUD_Title));

	UI_Title->StopBGM();
}

#pragma endregion

#pragma region Loading

bool UUI_HUD_Loading::IsLoadingCompleted()
{
	return Slider_Loading->IsLoadingCompleted();
}

#pragma endregion