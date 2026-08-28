// Copyright by 2025-2 WAP Game 2 team

#include "UI/HUD/Loading/UI_HUD_Loading.h"
#include "UI/HUD/Title/UI_HUD_Title.h"
#include "UI/Slider/Loading/UI_Slider_Loading.h"
#include "UI/Controller/UI_Controller.h"
#include "Player/Camera/EHPlayerCameraManager.h"
#include "Actor/SandClock/SandClock.h"
#include "GameSystem/GameInstance/EHGameInstance.h"
#include <Kismet/GameplayStatics.h>

#pragma region Active

void UUI_HUD_Loading::ActiveWidget()
{
	Super::ActiveWidget();

	SpawnSandClock();
}

#pragma endregion

#pragma region Show & Hide

void UUI_HUD_Loading::ShowWidget()
{
	Super::ShowWidget();

	SandClock->StartRotateClock();

	Slider_Loading->ResetLoadingPercentage();
	Slider_Loading->bStartLoading = true;

	GetWorld()->GetTimerManager().SetTimer(WaitHandle, FTimerDelegate::CreateWeakLambda(this, [this]()
		{
			if (Slider_Loading->IsLoadingCompleted())
			{
				StartLoadingEyeEffect();
				GetWorld()->GetTimerManager().ClearTimer(WaitHandle);
			}
		}), 0.01f, true);
}

void UUI_HUD_Loading::HideWidget()
{
	SandClock->StopRotateClock();

	Slider_Loading->bStartLoading = false;

	auto* GameInstance = GetGameInstance<UEHGameInstance>();
	GameInstance->SwitchDataLayer(EMapDataLayer::Hotel);

	Super::HideWidget();
}

#pragma endregion

#pragma region EyeEffect

void UUI_HUD_Loading::StartLoadingEyeEffect()
{
	Slider_Loading->bStartLoading = false;

	SetVisibility(ESlateVisibility::Hidden);

	auto* CameraManager = Cast<AEHPlayerCameraManager>(UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0));
	const float Duration = CameraManager->LoadingEyeEffect();

	auto* UICon = GetGameInstance()->GetSubsystem<UUI_Controller>();
	auto* UI_Title = Cast<UUI_HUD_Title>(UICon->GetCachedWidget(EWidgetType::HUD_Title));
	UI_Title->StopBGM(Duration);

	FTimerHandle ChangeHandle;
	GetWorld()->GetTimerManager().SetTimer(ChangeHandle, FTimerDelegate::CreateWeakLambda(this, [this, UICon]()
		{
			UICon->OpenWidget(EWidgetType::HUD_InGame);
		}), Duration, false);
}

#pragma endregion

#pragma region SandClock

void UUI_HUD_Loading::SpawnSandClock()
{
	if (!IsValid(SandClock))
	{
		SandClock = GetWorld()->SpawnActor<ASandClock>(SandClockClass, ClockSpawnTrans);
	}
}

#pragma endregion