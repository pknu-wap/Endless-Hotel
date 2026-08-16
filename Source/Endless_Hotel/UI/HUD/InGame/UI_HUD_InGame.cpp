// Copyright by 2025-2 WAP Game 2 team

#include "UI/HUD/InGame/UI_HUD_InGame.h"
#include "UI/Controller/UI_Controller.h"
#include "GameSystem/SubSystem/FloorProgressSubsystem.h"
#include "GameSystem/SubSystem/AnomalyPoolSubsystem.h"
#include "GameSystem/SubSystem/AnomalyVerdictSubsystem.h"
#include "GameSystem/SaveGame/SaveManager.h"
#include "GameSystem/Enum/EnumConverter.h"
#include "Player/Character/EHPlayer.h"
#include <Components/Image.h>
#include <Components/BackgroundBlur.h>
#include <Components/TextBlock.h>
#include <Components/VerticalBox.h>
#include <Kismet/GameplayStatics.h>

#pragma region Base

void UUI_HUD_InGame::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	AEHPlayer* Player = Cast<AEHPlayer>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	Player->CanInteract.AddDynamic(this, &ThisClass::ChangeCrosshair);

	auto* FloorSub = GetGameInstance()->GetSubsystem<UFloorProgressSubsystem>();
	auto* AnomalySub = GetGameInstance()->GetSubsystem<UAnomalyPoolSubsystem>();
	auto* VerdictSub = GetGameInstance()->GetSubsystem<UAnomalyVerdictSubsystem>();
	FloorSub->GameClearEvent.AddDynamic(this, &ThisClass::OpenDemoWidget);
	AnomalySub->OnAddAnomalyRule.AddDynamic(this, &ThisClass::AddDebugAnomalyRule);
	VerdictSub->OnAnomalySpawned.AddDynamic(this, &ThisClass::ChangeDebugAnomaly);

	AddDebugAnomalyRule(EAnomalyRule::None);
	ChangeDebugAnomaly();
}

#pragma endregion

#pragma region Show

void UUI_HUD_InGame::ShowWidget()
{
	Super::ShowWidget();

	auto Data = USaveManager::LoadData_Setting();
	SetBrightness(0.05f + Data.Brightness * 0.95f);
}

void UUI_HUD_InGame::StartInGameHUD(bool bIsStart)
{
	ShowCrosshair(bIsStart);
	EyeEffectBlur(!bIsStart, 0.5f);
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

void UUI_HUD_InGame::ShowCrosshair(bool bIsStart)
{
	if (bIsStart)
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

void UUI_HUD_InGame::EyeEffectBlur(bool bIsStart, float Value)
{
	const float TargetStrength = bIsStart ? 20.f : 0.f;
	CurrentStrength = bIsStart ? 0.f : 20.f;

	GetWorld()->GetTimerManager().SetTimer(BlurHandle, FTimerDelegate::CreateWeakLambda(this, [this, TargetStrength, Value, bIsStart]()
		{
			const float AddValue = bIsStart ? 0.1f * Value : -0.1f * Value;
			CurrentStrength += AddValue;
			BackBlur->SetBlurStrength(CurrentStrength);

			if (bIsStart && CurrentStrength >= TargetStrength)
			{
				GetWorld()->GetTimerManager().ClearTimer(BlurHandle);
			}
			else if (!bIsStart && CurrentStrength <= TargetStrength)
			{
				GetWorld()->GetTimerManager().ClearTimer(BlurHandle);
			}
		}), 0.01f, true);
}

void UUI_HUD_InGame::RemoveEyeEffectBlur()
{
	BackBlur->SetBlurStrength(0.f);
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

#pragma region Debug

void UUI_HUD_InGame::ShowDebugGameInfo(bool bActive)
{
	ESlateVisibility Active = bActive ? ESlateVisibility::Visible : ESlateVisibility::Hidden;
	Text_Rule->SetVisibility(Active);
	VB_Rule->SetVisibility(Active);
	Text_Current->SetVisibility(Active);
	Text_Next->SetVisibility(Active);
}

void UUI_HUD_InGame::AddDebugAnomalyRule(EAnomalyRule NewRule)
{
	VB_Rule->ClearChildren();

	auto* AnomalySub = GetGameInstance()->GetSubsystem<UAnomalyPoolSubsystem>();
	for (auto Rule : AnomalySub->AnomalyRules)
	{
		UTextBlock* TextBlock = NewObject<UTextBlock>(this);
		TextBlock->SetText(EnumConverter::GetEnumAsText<EAnomalyRule>(Rule));

		VB_Rule->AddChildToVerticalBox(TextBlock);
	}
}

void UUI_HUD_InGame::ChangeDebugAnomaly()
{
	auto* VerdictSub = GetGameInstance()->GetSubsystem<UAnomalyVerdictSubsystem>();

	Text_Current->SetText(FText::Format(FText::FromString(TEXT("현재: {0}")), EnumConverter::GetEnumAsText<EAnomalyID>(VerdictSub->CurrentAnomalyID)));
	Text_Next->SetText(FText::Format(FText::FromString(TEXT("다음: {0}")), EnumConverter::GetEnumAsText<EAnomalyID>(VerdictSub->NextAnomalyID)));
}

#pragma endregion