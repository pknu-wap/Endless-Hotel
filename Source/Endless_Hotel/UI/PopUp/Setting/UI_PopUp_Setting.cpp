// Copyright by 2025-2 WAP Game 2 team

#include "UI/PopUp/Setting/UI_PopUp_Setting.h"
#include "UI/PopUp/Setting/UI_PopUp_Option.h"
#include "UI/Button/Setting/UI_Button_Category.h"
#include "GameSystem/GameInstance/EHGameInstance.h"
#include "GameSystem/SaveGame/SaveManager.h"
#include "Player/Camera/EHPlayerCameraManager.h"
#include "Asset/DataAsset/Widget/PDA_Setting.h"
#include <Components/Button.h>
#include <Components/AudioComponent.h>
#include <Components/SpotLightComponent.h>
#include <Components/ExponentialHeightFogComponent.h>
#include <Components/CanvasPanel.h>
#include <Components/CanvasPanelSlot.h>
#include <GameFramework/GameUserSettings.h>
#include <Kismet/GameplayStatics.h>
#include <Engine/StaticMeshActor.h>

#pragma region Base

void UUI_PopUp_Setting::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	Button_Apply->OnClicked.AddDynamic(this, &ThisClass::Click_Apply);
	Button_Cancel->OnClicked.AddDynamic(this, &ThisClass::Input_ESC);

	CreateOptionWidgets();
	FindCategoryButton();
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

	Data_Setting = USaveManager::LoadData_Setting();

	SetVisibility(ESlateVisibility::Hidden);

	FindGearActor();

	auto* GameInstance = GetGameInstance<UEHGameInstance>();
	const EMapDataLayer Current = GameInstance->GetCurrentDataLayer();
	const float PossessDuration = Current == EMapDataLayer::Lobby ? 1.f : 0.f;
	auto* CameraManager = Cast<AEHPlayerCameraManager>(UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0));
	CameraManager->PossessCamera(ECameraType::Gear, PossessDuration);

	const float ShowDuration = Current == EMapDataLayer::Lobby ? 1.f : 0.01f;
	FTimerHandle ShowHandle;
	GetWorld()->GetTimerManager().SetTimer(ShowHandle, FTimerDelegate::CreateWeakLambda(this, [this, PossessDuration]()
		{
			ShowCurrentCategoryWidget();
			SetVisibility(ESlateVisibility::SelfHitTestInvisible);
			TurnOnGearLight(true);
		}), ShowDuration, false);

	if (!IsValid(AC_Gear))
	{
		AC_Gear = UGameplayStatics::CreateSound2D(GetWorld(), SW_Gear);
		AC_Gear->SetAutoActivate(false);
	}
}

void UUI_PopUp_Setting::HideWidget()
{
	bRotateGear = false;

	AC_Gear->Stop();

	TurnOnGearLight(false);

	auto* GameInstance = GetGameInstance<UEHGameInstance>();
	auto* CameraManager = Cast<AEHPlayerCameraManager>(UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0));
	GameInstance->GetCurrentDataLayer() == EMapDataLayer::Lobby ? CameraManager->PossessCamera(ECameraType::Title, 1.f) : CameraManager->PossessCameraToPlayer(0.f);
	GameInstance->ActiveAdditionalDataLayer(EMapDataLayer::Lobby, false);

	Super::HideWidget();
}

#pragma endregion

#pragma region Option

void UUI_PopUp_Setting::CreateOptionWidgets()
{
	UCanvasPanel* Canvas = Cast<UCanvasPanel>(GetRootWidget());

	for (const auto& Pair : PDA_Setting->Setting)
	{
		ESettingCategory Category = Pair.Key;
		FOptionList OptionList = Pair.Value;

		auto* ChildWidget = CreateWidget<UUI_PopUp_Option>(this, OptionList.Class.LoadSynchronous());
		ChildWidget->InitOption(OptionList);
		OptionWidgets.Add(Category, ChildWidget);

		UCanvasPanelSlot* CanvasSlot = Canvas->AddChildToCanvas(ChildWidget);
		CanvasSlot->SetAnchors(FAnchors(0.0f, 0.0f, 1.0f, 1.0f));
		CanvasSlot->SetOffsets(FMargin(0.0f));
	}
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

	AC_Gear->FadeIn(0.5f, 1, 0);

	TurnOnGearLight(false);
}

void UUI_PopUp_Setting::FindGearActor()
{
	if (IsValid(SM_Gear))
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

	CategoryButtons[CategoryIndex]->Click_Button();

	return Super::NativeOnMouseWheel(InGeometry, InMouseEvent);
}

#pragma endregion

#pragma region Category

void UUI_PopUp_Setting::FindCategoryButton()
{
	CategoryButtons.Empty();

	for (auto* Child : UI_Gear->GetAllChildren())
	{
		if (auto* Target = Cast<UUI_Button_Category>(Child))
		{
			CategoryButtons.Add(Target);
		}
	}
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

void UUI_PopUp_Setting::ShowCurrentCategoryWidget()
{
	for (const auto& Target : OptionWidgets)
	{
		Target.Value->HideWidget();
		if (Target.Key == CurrentCategory)
		{
			Target.Value->ShowWidget();
		}
	}
}

#pragma endregion