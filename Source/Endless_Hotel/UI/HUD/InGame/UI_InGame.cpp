// Copyright by 2025-2 WAP Game 2 team

#include "UI/HUD/InGame/UI_InGame.h"
#include "UI/Controller/UI_Controller.h"
#include "GameSystem/SubSystem/AnomalyProgressSubSystem.h"
#include "GameSystem/SaveGame/SaveManager.h"
#include "Player/Character/EHPlayer.h"
#include "Elevator/Elevator.h"
#include <Components/Image.h>
#include <Kismet/GameplayStatics.h>

#pragma region Base

void UUI_InGame::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	AEHPlayer* EHPlayer = Cast<AEHPlayer>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	EHPlayer->CanInteract.AddDynamic(this, &ThisClass::ChangeCrosshair);

	auto* Subsystem = GetGameInstance()->GetSubsystem<UAnomalyProgressSubSystem>();
	Subsystem->GameClearEvent.AddDynamic(this, &ThisClass::OpenDemoWidget);

	AElevator::ElevatorDelegate.AddDynamic(this, &ThisClass::ShowCrosshair);
}

#pragma endregion

#pragma region Crosshair

void UUI_InGame::ChangeCrosshair(bool bCanInteract)
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

void UUI_InGame::ShowCrosshair(bool bIsShow)
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

void UUI_InGame::SetBrightness(float Value)
{
	FLinearColor Color = Image_Brightness->GetColorAndOpacity();
	Color.A = (1 - Value) * 0.8f;
	Image_Brightness->SetColorAndOpacity(Color);
}

#pragma endregion

#pragma region Demo

void UUI_InGame::OpenDemoWidget()
{
	UUI_Controller* UICon = GetGameInstance()->GetSubsystem<UUI_Controller>();
	UICon->OpenWidget(UI_Demo);
}

#pragma endregion