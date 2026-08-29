// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "UI/PopUp/UI_PopUp_Base.h"
#include "Type/UI/Type_Setting.h"
#include "Type/Save/Type_Save.h"
#include <CoreMinimal.h>
#include <UI_PopUp_Setting.generated.h>

UCLASS()
class ENDLESS_HOTEL_API UUI_PopUp_Setting : public UUI_PopUp_Base
{
	GENERATED_BODY()

#pragma region Base

protected:
	virtual void NativeOnInitialized() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

#pragma endregion

#pragma region Show & Hide

public:
	virtual void ShowWidget() override;
	virtual void HideWidget() override;

#pragma endregion

#pragma region Data

private:
	UPROPERTY(EditDefaultsOnly, Category = "Data")
	TObjectPtr<class UPDA_Setting> PDA_Setting;

#pragma endregion

#pragma region Option

public:
	FSaveData_Setting& GetSettingData() { return Data_Setting; }
	void ShowOptionWidget(ESettingCategory Category);

private:
	void CreateOptionWidgets();

private:
	FSaveData_Setting Data_Setting;

	UPROPERTY(EditDefaultsOnly, Category = "Option")
	TSubclassOf<class UUI_PopUp_Option> OptionClass;

	UPROPERTY()
	TMap<ESettingCategory, TObjectPtr<class UUI_PopUp_Option>> OptionWidgets;

#pragma endregion

#pragma region Gear

public:
	void StartRotateGear(float Target);

private:
	void FindGearActor();
	void RotateGear(float InDeltaTime);
	const int32 GetShortestAdditionAngle(int32 Cur, int32 Tar);
	void TurnOnGearLight(bool bOn);

private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UCanvasPanel> UI_Gear;

	UPROPERTY(EditDefaultsOnly, Category = "Sound")
	TObjectPtr<class USoundWave> SW_Gear;

	UPROPERTY()
	TObjectPtr<class AStaticMeshActor> SM_Gear;

	UPROPERTY()
	TObjectPtr<class USpotLightComponent> Comp_SpotLight;

	UPROPERTY()
	TObjectPtr<class UExponentialHeightFogComponent> Comp_Fog;

	UPROPERTY()
	TObjectPtr<class UAudioComponent> AC_Gear;

private:
	// UI
	float CurrentAngle = 0.f;
	float FinalAngle = 0.f;
	const float RotateSpeed = 45.f;

	// Actor
	FRotator OriginRot;
	FQuat CurrentQuat;
	FQuat FinalQuat;

	FTimerHandle LightHandle;

	bool bRotateGear = false;

#pragma endregion

#pragma region Control

private:
	virtual FReply NativeOnMouseWheel(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

	UFUNCTION()
	void Click_Apply();

private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UButton> Button_Apply;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UButton> Button_Cancel;

#pragma endregion

#pragma region Category

private:
	void FindCategoryButton();
	void AdjustCategoryIndex(bool bUp);

private:
	UPROPERTY()
	TArray<TObjectPtr<class UUI_Button_Category>> CategoryButtons;

	int8 CategoryIndex = 0;

#pragma endregion

};