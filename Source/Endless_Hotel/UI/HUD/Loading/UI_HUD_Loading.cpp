// Copyright by 2025-2 WAP Game 2 team

#include "UI/HUD/Loading/UI_HUD_Loading.h"
#include "UI/HUD/Title/UI_HUD_Title.h"
#include "UI/Slider/Loading/UI_Slider_Loading.h"
#include "UI/Controller/UI_Controller.h"
#include "Player/Camera/EHPlayerCameraManager.h"
#include "Actor/SandClock/SandClock.h"
#include <Kismet/GameplayStatics.h>

#pragma region Show

void UUI_HUD_Loading::ShowWidget()
{
	if (!IsValid(SandClock))
	{
		SandClock = GetWorld()->SpawnActor<ASandClock>(SandClockClass, ClockSpawnTrans);
	}

	bIsCompletedEyeEffect = false;

	constexpr float PossessDuration = 2.f;
	auto* CameraManager = Cast<AEHPlayerCameraManager>(UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0));
	CameraManager->PossessCamera(ECameraType::SandClock, PossessDuration);

	GetWorld()->GetTimerManager().SetTimer(PossessHandle, this, &ThisClass::OnPossessedCamera, PossessDuration, false);
}

void UUI_HUD_Loading::HideWidget()
{
	SandClock->StopRotateClock();

	Super::HideWidget();
}

#pragma endregion

#pragma region Loading

bool UUI_HUD_Loading::IsLoadingCompleted()
{
	return Slider_Loading->IsLoadingCompleted();
}

void UUI_HUD_Loading::OnPossessedCamera()
{
	SandClock->StartRotateClock();

	Slider_Loading->ResetLoadingPercentage();
	Slider_Loading->bStartLoading = true;

	Super::ShowWidget();
}

#pragma endregion

#pragma region EyeEffect

void UUI_HUD_Loading::StartLoadingEyeEffect()
{
	Slider_Loading->bStartLoading = false;

	auto* UICon = GetGameInstance()->GetSubsystem<UUI_Controller>();
	auto* UI_Title = Cast<UUI_HUD_Title>(UICon->GetCachedWidget(EWidgetType::HUD_Title));

	constexpr float StopDuration = 2.f;
	UI_Title->StopBGM(StopDuration);

	SetVisibility(ESlateVisibility::Hidden);

	auto* CameraManager = Cast<AEHPlayerCameraManager>(UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0));
	CameraManager->LoadingEyeEffect();

	constexpr float WaitDuration = 2.f;
	GetWorld()->GetTimerManager().SetTimer(WaitHandle, this, &ThisClass::WaitEyeEffect, WaitDuration, false);
}

void UUI_HUD_Loading::WaitEyeEffect()
{
	bIsCompletedEyeEffect = true;
}

#pragma endregion