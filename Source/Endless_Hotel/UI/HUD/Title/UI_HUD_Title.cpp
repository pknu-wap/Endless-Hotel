// Copyright by 2025-2 WAP Game 2 team

#include "UI/HUD/Title/UI_HUD_Title.h"
#include "GameSystem/SaveGame/SaveManager.h"
#include "Player/Camera/EHPlayerCameraManager.h"
#include <Components/AudioComponent.h>
#include <Components/Image.h>
#include <Kismet/GameplayStatics.h>

#pragma region Active

void UUI_HUD_Title::ActiveWidget()
{
	Super::ActiveWidget();

	PlayBGM();

	auto* CameraManager = Cast<AEHPlayerCameraManager>(UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0));
	CameraManager->PossessCamera(ECameraType::Title);
}

#pragma endregion

#pragma region Show

void UUI_HUD_Title::ShowWidget()
{
	Super::ShowWidget();

	SetLogoImage();

	constexpr float Duration = 1.f;
	auto* CameraManager = Cast<AEHPlayerCameraManager>(UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0));
	CameraManager->PossessCamera(ECameraType::Title, Duration);
}

#pragma endregion

#pragma region Logo

void UUI_HUD_Title::SetLogoImage()
{
	if (!USaveManager::LoadData_GameClear())
	{
		Image_Logo->SetBrushFromTexture(Texture_NoClear);
		return;
	}

	Image_Logo->SetBrushFromTexture(Texture_Clear);
}

#pragma endregion

#pragma region BGM

void UUI_HUD_Title::StopBGM(float Duration)
{
	AC->OnAudioFinished.Clear();
	AC->FadeOut(Duration, 0.f);
	AC = nullptr;
}

void UUI_HUD_Title::PlayBGM()
{
	if (!IsValid(AC))
	{
		AC = UGameplayStatics::CreateSound2D(GetWorld(), SW_BGM);
		AC->OnAudioFinished.AddUniqueDynamic(this, &ThisClass::PlayBGM);
	}

	AC->Play();
}

#pragma endregion