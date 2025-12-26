// Copyright by 2025-2 WAP Game 2 team

#include "UI/Base/InGame/UI_InGame.h"
#include "UI/Controller/UI_Controller.h"
#include "UI/PopUp/Default/Setting/UI_PopUp_Brightness.h"
#include "GameSystem/SubSystem/AnomalyProgressSubSystem.h"
#include "GameSystem/SaveGame/SaveManager.h"
#include "Components/Image.h"
#include "Components/CanvasPanelSlot.h"
#include "Player/Character/EHPlayer.h"
#include "Kismet/GameplayStatics.h"

#pragma region Base

void UUI_InGame::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	AEHPlayer* EHPlayer = Cast<AEHPlayer>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	EHPlayer->CanInteract.AddDynamic(this, &ThisClass::ChangeCrosshair);

	auto* Subsystem = GetGameInstance()->GetSubsystem<UAnomalyProgressSubSystem>();
	Subsystem->GameClearEvent.AddDynamic(this, &ThisClass::OpenDemoWidget);

	UUI_PopUp_Brightness::SettingBrightness.AddDynamic(this, &ThisClass::SetBrightness);
}

void UUI_InGame::NativeConstruct()
{
	Super::NativeConstruct();

	SetBrightness();
}

#pragma endregion

#pragma region Crosshair

void UUI_InGame::ChangeCrosshair(bool bCanInteract)
{
	UCanvasPanelSlot* CPSlot = Cast<UCanvasPanelSlot>(Crosshair->Slot);

	FSlateBrush Brush;

	if (bCanInteract)
	{
		Brush.SetResourceObject(Crosshair_Interact);
		Brush.TintColor = FSlateColor(FLinearColor(1, 1, 1, 0.5f));
		CPSlot->SetSize(FVector2D(20, 20));
		CPSlot->SetPosition(FVector2D(-10, -10));
	}
	else
	{
		Brush.SetResourceObject(Crosshair_Normal);
		Brush.TintColor = FSlateColor(FLinearColor(1, 1, 1, 0.3f));
		CPSlot->SetSize(FVector2D(14, 14));
		CPSlot->SetPosition(FVector2D(-7, -7));
	}

	Crosshair->SetBrush(Brush);
}

#pragma endregion

#pragma region Brightness

void UUI_InGame::SetBrightness()
{
	FLinearColor ColorValue = Image_Brightness->GetColorAndOpacity();
	ColorValue.A = (1 - USaveManager::LoadSettingData().Value_Brightness) * 0.6f;
	Image_Brightness->SetColorAndOpacity(ColorValue);
}

#pragma endregion

#pragma region Demo

void UUI_InGame::OpenDemoWidget()
{
	UUI_Controller* UICon = GetGameInstance()->GetSubsystem<UUI_Controller>();
	UICon->OpenWidget(UI_Demo, EWidgetType::PopUp, EInputModeType::UIOnly);
}

#pragma endregion