// Copyright by 2025-2 WAP Game 2 team

#include "UI/HUD/InGame/UI_HUD_InGame.h"
#include "UI/Controller/UI_Controller.h"
#include "GameSystem/SubSystem/FloorProgressSubsystem.h"
#include "GameSystem/SubSystem/AnomalyPoolSubsystem.h"
#include "GameSystem/SubSystem/AnomalyVerdictSubsystem.h"
#include "GameSystem/SaveGame/SaveManager.h"
#include "GameSystem/Enum/EnumConverter.h"
#include "Player/Character/EHPlayer.h"
#include "Player/Camera/EHPlayerCameraManager.h"
#include <Components/Image.h>
#include <Components/BackgroundBlur.h>
#include <Components/TextBlock.h>
#include <Components/VerticalBox.h>
#include <Kismet/GameplayStatics.h>

#pragma region Base

void UUI_HUD_InGame::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	auto* Player = Cast<AEHPlayer>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	Player->CanInteract.AddUObject(this, &ThisClass::ChangeCrosshair);
	Player->OnDie.AddWeakLambda(this, [this](const EDeathReason&) {StartInGameHUD(false); });
	Player->OnRevive.AddWeakLambda(this, [this]() {StartInGameHUD(true); });

	auto* AnomalySub = GetGameInstance()->GetSubsystem<UAnomalyPoolSubsystem>();
	auto* VerdictSub = GetGameInstance()->GetSubsystem<UAnomalyVerdictSubsystem>();
	AnomalySub->OnAddAnomalyRule.AddDynamic(this, &ThisClass::AddDebugAnomalyRule);
	VerdictSub->OnAnomalySpawned.AddDynamic(this, &ThisClass::ChangeDebugAnomaly);
}

#pragma endregion

#pragma region Active

void UUI_HUD_InGame::ActiveWidget()
{
	Super::ActiveWidget();

	AddDebugAnomalyRule(EAnomalyRule::None);
	ChangeDebugAnomaly();

	bool bCheckInState = USaveManager::LoadData_Progression().Progression == EGameProgression::CheckIn;
	const float Duration = bCheckInState ? 2.f : 0.f;

	auto* CameraManager = Cast<AEHPlayerCameraManager>(UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0));
	CameraManager->PossessCameraToPlayer(Duration);

	if (!bCheckInState)
	{
		CameraManager->StartEyeEffect(true);
		StartInGameHUD(true);
	}
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

#pragma region Effect

void UUI_HUD_InGame::StartInGameHUD(bool bIsStart)
{
	ShowCrosshair(bIsStart);
	EyeEffectBlur(!bIsStart, 0.5f);
}

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

#pragma endregion

#pragma region Crosshair

void UUI_HUD_InGame::ChangeCrosshair(bool bCanInteract)
{
	if (bCanInteract == bIsCrosshairInteractMode)
	{
		return;
	}

	UWidgetAnimation* TargetAnim = bCanInteract ? WidgetAnim_Interact : WidgetAnim_Normal;
	PlayAnimation(TargetAnim);

	bIsCrosshairInteractMode = !bIsCrosshairInteractMode;
}

void UUI_HUD_InGame::ShowCrosshair(bool bIsStart)
{
	if (!bIsStart)
	{
		return;
	}

	PlayAnimation(WidgetAnim_ShowCrosshair);
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
			Image_SubTitle->SetVisibility(ESlateVisibility::Hidden);
			Text_SubTitle->SetVisibility(ESlateVisibility::Hidden);
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