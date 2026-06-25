// Copyright by 2025-2 WAP Game 2 team

#include "UI/PopUp/Setting/UI_PopUp_Setting.h"
#include "UI/PopUp/Setting/UI_PopUp_Option.h"
#include "UI/Button/Setting/UI_Button_Setting.h"
#include "GameSystem/GameInstance/EHGameInstance.h"
#include "GameSystem/SaveGame/SaveManager.h"
#include "Player/Camera/EHPlayerCameraManager.h"
#include <Components/Button.h>
#include <Components/Border.h>
#include <Components/TextBlock.h>
#include <Components/AudioComponent.h>
#include <Components/SpotLightComponent.h>
#include <Components/ExponentialHeightFogComponent.h>
#include <Components/CanvasPanel.h>
#include <GameFramework/GameUserSettings.h>
#include <Kismet/GameplayStatics.h>
#include <Engine/StaticMeshActor.h>

#pragma region Declare

UUI_PopUp_Setting::FSettingHighlight UUI_PopUp_Setting::Highlight;

#pragma endregion

#pragma region Base

void UUI_PopUp_Setting::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	Button_Normal->OnClicked.AddDynamic(this, &ThisClass::Click_Normal);
	Button_Input->OnClicked.AddDynamic(this, &ThisClass::Click_Input);

	Button_Apply->OnClicked.AddDynamic(this, &ThisClass::Click_Apply);
	Button_Cancel->OnClicked.AddDynamic(this, &ThisClass::Input_ESC);

	Highlight.AddDynamic(this, &ThisClass::HighlightButtons);

	CategoryButtons.Empty();

	for (auto* Check : UI_Gear->GetAllChildren())
	{
		if (auto* Target = Cast<UUI_Button_Setting>(Check))
		{
			CategoryButtons.Add(Target);
		}
	}
}

void UUI_PopUp_Setting::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (bRotateGear)
	{
		RotateGear(InDeltaTime);
	}
}

#pragma endregion

#pragma region Show & Hide

void UUI_PopUp_Setting::ShowWidget()
{
	Super::ShowWidget();

	SetVisibility(ESlateVisibility::Collapsed);

	auto* GameInstance = GetGameInstance<UEHGameInstance>();
	WidgetOpenedDataLayer = GameInstance->GetCurrentDataLayer();
	GameInstance->SwitchDataLayer(EMapDataLayer::Lobby, false);

	auto* CameraManager = Cast<AEHPlayerCameraManager>(UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0));

	switch (WidgetOpenedDataLayer)
	{
	case EMapDataLayer::Lobby:
	{
		FTimerHandle ShowHandle;
		GetWorld()->GetTimerManager().SetTimer(ShowHandle, FTimerDelegate::CreateWeakLambda(this, [this]()
			{
				HighlightButtons();
				FindGearActor();
				SetVisibility(ESlateVisibility::SelfHitTestInvisible);
				TurnOnGearLight(true);
			}), 1.f, false);

		CameraManager->PossessCamera(ECameraType::Gear, 1.f);
		break;
	}
	default:
	{
		SetVisibility(ESlateVisibility::SelfHitTestInvisible);

		FTimerHandle ShowHandle;
		GetWorld()->GetTimerManager().SetTimer(ShowHandle, FTimerDelegate::CreateWeakLambda(this, [this]()
			{
				HighlightButtons();
				FindGearActor();
				TurnOnGearLight(true);
			}), 1.f, false);

		CameraManager->PossessCamera(ECameraType::Gear, 0.f);
		break;
	}
	}
}

void UUI_PopUp_Setting::HideWidget()
{
	Super::HideWidget();

	auto* GameInstance = GetGameInstance<UEHGameInstance>();
	auto* CameraManager = Cast<AEHPlayerCameraManager>(UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0));

	switch (WidgetOpenedDataLayer)
	{
	case EMapDataLayer::Lobby:
		CameraManager->PossessCamera(ECameraType::Title, 1.f);
		break;

	default:
		GameInstance->SwitchDataLayer(WidgetOpenedDataLayer, false);
		CameraManager->PossessCameraToPlayer(0.f);
		break;
	}

	SM_Gear->SetActorRotation(OriginRot);

	TurnOnGearLight(false);
}

#pragma endregion

#pragma region Highlight

void UUI_PopUp_Setting::HighlightButtons()
{
	Data_Setting = USaveManager::LoadData_Setting();

	UI_Screen->HighlightOptions();
	UI_Grapic->HighlightOptions();
	UI_Sound->HighlightOptions();
	UI_Control_Normal->HighlightOptions();
	UI_Control_Input->HighlightOptions();
	UI_Gameplay->HighlightOptions();
	UI_System->HighlightOptions();

	Border_HideBox->SetVisibility(ESlateVisibility::Collapsed);
}

#pragma endregion

#pragma region Category

void UUI_PopUp_Setting::SetCurrentCategoryText(FText Value)
{
	Text_CurrentCategory->SetText(Value);
}

#pragma endregion

#pragma region Option

void UUI_PopUp_Setting::ShowCategoryOption(ESettingCategory Target)
{
	UI_Screen->SetVisibility(ESlateVisibility::Collapsed);
	UI_Grapic->SetVisibility(ESlateVisibility::Collapsed);
	UI_Sound->SetVisibility(ESlateVisibility::Collapsed);
	UI_Control_Normal->SetVisibility(ESlateVisibility::Collapsed);
	UI_Control_Input->SetVisibility(ESlateVisibility::Collapsed);
	UI_Gameplay->SetVisibility(ESlateVisibility::Collapsed);
	UI_System->SetVisibility(ESlateVisibility::Collapsed);

	Border_HideBox->SetVisibility(ESlateVisibility::Collapsed);
	Border_HideBox2->SetVisibility(ESlateVisibility::Collapsed);

	Button_Normal->SetVisibility(ESlateVisibility::Collapsed);
	Button_Input->SetVisibility(ESlateVisibility::Collapsed);

	switch (Target)
	{
	case ESettingCategory::Screen:
		UI_Screen->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		break;

	case ESettingCategory::Grapic:
	{
		UI_Grapic->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		if (Data_Setting.Grapic != EOptionValue::Custom)
		{
			Border_HideBox->SetVisibility(ESlateVisibility::Visible);
		}
		break;
	}

	case ESettingCategory::Sound:
		UI_Sound->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		break;

	case ESettingCategory::Control_Normal:
		UI_Control_Normal->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		Button_Normal->SetVisibility(ESlateVisibility::Visible);
		Button_Input->SetVisibility(ESlateVisibility::Visible);
		break;

	case ESettingCategory::Control_Input:
		UI_Control_Input->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		Button_Normal->SetVisibility(ESlateVisibility::Visible);
		Button_Input->SetVisibility(ESlateVisibility::Visible);
		break;

	case ESettingCategory::Gameplay:
	{
		UI_Gameplay->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		ESlateVisibility SlateVisibility = USaveManager::LoadData_GameClear() ? ESlateVisibility::Hidden : ESlateVisibility::Visible;
		Border_HideBox2->SetVisibility(SlateVisibility);
		break;
	}

	case ESettingCategory::System:
		UI_System->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		break;
	}
}

void UUI_PopUp_Setting::SetHideBoxVisibility(ESlateVisibility Option)
{
	Border_HideBox->SetVisibility(Option);
}

void UUI_PopUp_Setting::Click_Normal()
{
	UI_Control_Normal->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	UI_Control_Input->SetVisibility(ESlateVisibility::Collapsed);
}

void UUI_PopUp_Setting::Click_Input()
{
	UI_Control_Normal->SetVisibility(ESlateVisibility::Collapsed);
	UI_Control_Input->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
}

#pragma endregion

#pragma region Gear

void UUI_PopUp_Setting::StartRotateGear(float Target)
{
	if (Target == -1)
	{
		return;
	}

	const float AdditionAngle = GetShortestAdditionAngle(CurrentAngle, Target);
	FinalAngle = CurrentAngle + AdditionAngle;

	CurrentQuat = SM_Gear->GetActorQuat();
	FinalQuat = CurrentQuat * FQuat(FVector::UpVector, FMath::DegreesToRadians(AdditionAngle));

	bRotateGear = true;

	if (!IsValid(AC_Gear))
	{
		AC_Gear = UGameplayStatics::CreateSound2D(GetWorld(), SW_Gear);
	}

	AC_Gear->FadeIn(0.5f, 1, 0);

	TurnOnGearLight(false);
}

void UUI_PopUp_Setting::FindGearActor()
{
	if (SM_Gear.IsValid())
	{
		return;
	}

	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AActor::StaticClass(), OUT FoundActors);

	for (AActor* FoundActor : FoundActors)
	{
		if (FoundActor->ActorHasTag("Gear_StaticMesh"))
		{
			SM_Gear = Cast<AStaticMeshActor>(FoundActor);
			OriginRot = SM_Gear->GetActorRotation();
		}
		else if (FoundActor->ActorHasTag("Gear_SpotLight"))
		{
			Comp_SpotLight = FoundActor->FindComponentByClass<USpotLightComponent>();
		}
	}

	Comp_Fog = SM_Gear->FindComponentByClass<UExponentialHeightFogComponent>();
}

void UUI_PopUp_Setting::RotateGear(float InDeltaTime)
{
	CurrentAngle = FMath::FInterpConstantTo(CurrentAngle, FinalAngle, InDeltaTime, RotateSpeed);
	UI_Gear->SetRenderTransformAngle(CurrentAngle);

	CurrentQuat = FMath::QInterpConstantTo(CurrentQuat, FinalQuat, InDeltaTime, FMath::DegreesToRadians(RotateSpeed));
	SM_Gear->SetActorRotation(CurrentQuat);

	if (FMath::IsNearlyEqual(CurrentAngle, FinalAngle))
	{
		CurrentAngle = FinalAngle;
		UI_Gear->SetRenderTransformAngle(CurrentAngle);

		CurrentQuat = FinalQuat;
		SM_Gear->SetActorRotation(CurrentQuat);

		bRotateGear = false;

		AC_Gear->FadeOut(0.5f, 0);

		TurnOnGearLight(true);
	}
}

const int32 UUI_PopUp_Setting::GetShortestAdditionAngle(int32 Cur, int32 Tar)
{
	const int32 AngularSpacing = (Tar - Cur) % 360;

	if (AngularSpacing > 180)
	{
		return AngularSpacing - 360;
	}
	else if (AngularSpacing < -180)
	{
		return AngularSpacing + 360;
	}

	return AngularSpacing;
}

void UUI_PopUp_Setting::TurnOnGearLight(bool bOn)
{
	const float LightValue = bOn ? 100.f : 0.f;
	const float FogValue = bOn ? 2.f : 0.f;
	constexpr float Speed = 1000.f;

	UWorld* World = GetWorld();
	World->GetTimerManager().ClearTimer(LightHandle);
	World->GetTimerManager().SetTimer(LightHandle, FTimerDelegate::CreateWeakLambda(this, [this, LightValue, World, Speed]()
		{
			const float Target = FMath::FInterpConstantTo(Comp_SpotLight->Intensity, LightValue, World->GetDeltaSeconds(), Speed);
			Comp_SpotLight->SetIntensity(Target);

			if (FMath::IsNearlyEqual(Target, LightValue))
			{
				Comp_SpotLight->SetIntensity(LightValue);
				World->GetTimerManager().ClearTimer(LightHandle);
			}
		}), World->GetDeltaSeconds(), true);
	
	Comp_Fog->SetFogDensity(FogValue);
}

#pragma endregion

#pragma region Control

void UUI_PopUp_Setting::Click_Apply()
{
	auto* SettingHandle = UGameUserSettings::GetGameUserSettings();
	SettingHandle->SaveSettings();
	SettingHandle->ApplySettings(false);

	USaveManager::SaveData_Setting(Data_Setting);

	Input_ESC();
}

FReply UUI_PopUp_Setting::NativeOnMouseWheel(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	if (bRotateGear)
	{
		return FReply::Handled();
	}

	const float WheelDelta = InMouseEvent.GetWheelDelta();

	if (WheelDelta > 0.f)
	{
		AdjustCategoryIndex(true);
	}
	else if (WheelDelta < 0.f)
	{
		AdjustCategoryIndex(false);
	}

	CategoryButtons[CategoryIndex]->ClickCategoryButton();

	return Super::NativeOnMouseWheel(InGeometry, InMouseEvent);
}

void UUI_PopUp_Setting::AdjustCategoryIndex(bool bUp)
{
	CategoryIndex = bUp ? CategoryIndex + 1 : CategoryIndex - 1;

	int32 MaxIndex = CategoryButtons.Num() - 1;

	if (CategoryIndex < 0)
	{
		CategoryIndex = MaxIndex;
	}
	else if (CategoryIndex > MaxIndex)
	{
		CategoryIndex = 0;
	}
}

#pragma endregion