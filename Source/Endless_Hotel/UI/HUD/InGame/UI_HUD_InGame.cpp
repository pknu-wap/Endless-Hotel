// Copyright by 2025-2 WAP Game 2 team

#include "UI/HUD/InGame/UI_HUD_InGame.h"
#include "UI/Controller/UI_Controller.h"
#include "GameSystem/SubSystem/GameSystem.h"
#include "GameSystem/SaveGame/SaveManager.h"
#include "Player/Character/EHPlayer.h"
#include <Components/Image.h>
#include <Components/BackgroundBlur.h>
#include <Components/TextBlock.h>
#include <Kismet/GameplayStatics.h>

#pragma region Base

void UUI_HUD_InGame::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	AEHPlayer* Player = Cast<AEHPlayer>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	Player->CanInteract.AddDynamic(this, &ThisClass::ChangeCrosshair);

	auto* Subsystem = GetGameInstance()->GetSubsystem<UGameSystem>();
	Subsystem->GameClearEvent.AddDynamic(this, &ThisClass::OpenDemoWidget);
}

#pragma endregion

#pragma region Show

void UUI_HUD_InGame::ShowWidget()
{
	Super::ShowWidget();

	auto Data = USaveManager::LoadData_Setting();
	SetBrightness(0.05f + Data.Brightness * 0.95f);
}

#pragma endregion

#pragma region Crosshair

void UUI_HUD_InGame::ChangeCrosshair(bool bCanInteract)
{
	if (bCanInteract)
	{
		if (!bIsCrosshairInteractMode)
		{
			PlayAnimation(WidgetAnim_Interact);
			bIsCrosshairInteractMode = true;
		}
	}
	else
	{
		if (bIsCrosshairInteractMode)
		{
			PlayAnimation(WidgetAnim_Normal);
			bIsCrosshairInteractMode = false;
		}
	}
}

void UUI_HUD_InGame::ShowCrosshair(bool bIsShow)
{
	if (bIsShow)
	{
		PlayAnimation(WidgetAnim_ShowCrosshair);
	}
	else
	{
		Image_Crosshair_Center->SetVisibility(ESlateVisibility::Hidden);
	}
}

#pragma endregion

#pragma region Brightness

void UUI_HUD_InGame::SetBrightness(float Value)
{
	FLinearColor Color = Image_Brightness->GetColorAndOpacity();
	Color.A = (1 - Value) * 0.8f;
	Image_Brightness->SetColorAndOpacity(Color);
}

#pragma endregion

#pragma region Blur

void UUI_HUD_InGame::AnomalyBlur(bool bIsStart)
{
	if (!bIsStart)
	{
		BackBlur->SetBlurStrength(0.f);
		return;
	}

	const float TargetStrength = 20;
	float CurrentStrength = 0;

	GetWorld()->GetTimerManager().SetTimer(BlurHandle, FTimerDelegate::CreateWeakLambda(this, [this, TargetStrength, CurrentStrength]() mutable
		{
			CurrentStrength += 0.1f;
			BackBlur->SetBlurStrength(CurrentStrength);

			if (CurrentStrength >= TargetStrength)
			{
				GetWorld()->GetTimerManager().ClearTimer(BlurHandle);
			}
		}), 0.01f, true);
}

void UUI_HUD_InGame::EyeEffectBlur(bool bIsStart)
{
	float TargetStrength = 0;
	float CurrentStrength = 20;

	if (!bIsStart)
	{
		TargetStrength = 20;
		CurrentStrength = 0;
	}

	GetWorld()->GetTimerManager().SetTimer(BlurHandle, FTimerDelegate::CreateWeakLambda(this, [this, bIsStart, TargetStrength, CurrentStrength]() mutable
		{
			BackBlur->SetBlurStrength(CurrentStrength);

			if (bIsStart)
			{
				CurrentStrength -= 0.05f;

				if (CurrentStrength <= TargetStrength)
				{
					GetWorld()->GetTimerManager().ClearTimer(BlurHandle);
				}
			}
			else
			{
				CurrentStrength += 0.05f;

				if (CurrentStrength >= TargetStrength)
				{
					GetWorld()->GetTimerManager().ClearTimer(BlurHandle);
				}
			}
		}), 0.01f, true);
}

#pragma endregion

#pragma region Demo

void UUI_HUD_InGame::OpenDemoWidget()
{
	UUI_Controller* UICon = GetGameInstance()->GetSubsystem<UUI_Controller>();
	UICon->OpenWidget(EWidgetType::PopUp_Demo);
}

#pragma endregion

#pragma region SubTitle

void UUI_HUD_InGame::ShowSubTitle(FText SubTitle, float Delay, float Duration)
{
	FTimerHandle ShowHandle;
	GetWorld()->GetTimerManager().SetTimer(ShowHandle, FTimerDelegate::CreateWeakLambda(this, [this, SubTitle]()
		{
			Image_SubTitle->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
			Text_SubTitle->SetText(SubTitle);
			Text_SubTitle->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		}), Delay, false);

	FTimerHandle HideHandle;
	GetWorld()->GetTimerManager().SetTimer(HideHandle, FTimerDelegate::CreateWeakLambda(this, [this]()
		{
			Image_SubTitle->SetVisibility(ESlateVisibility::Collapsed);
			Text_SubTitle->SetVisibility(ESlateVisibility::Collapsed);
		}), Delay + Duration, false);
}

#pragma endregion