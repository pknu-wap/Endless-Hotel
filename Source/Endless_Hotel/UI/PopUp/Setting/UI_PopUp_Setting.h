// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "UI/PopUp/UI_PopUp_Base.h"
#include <CoreMinimal.h>
#include <UI_PopUp_Setting.generated.h>

UCLASS(Meta = (DisableNativeTick))
class ENDLESS_HOTEL_API UUI_PopUp_Setting : public UUI_PopUp_Base
{
	GENERATED_BODY()
	
#pragma region Base

protected:
	virtual void NativeOnInitialized() override;

#pragma endregion

#pragma region Category

public:
	void SetCurrentCategoryText(FText Value);

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> Text_CurrentCategory;

#pragma endregion

#pragma region Gear

public:
	void RotateGear(float TargetAngle);

protected:
	const float GetShortestAddAngle(float Cur, float Tar);

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UUserWidget> UI_Gear;

	FTimerHandle AngleHandle;
	float CurrentAngle = 0;

#pragma endregion

#pragma region Control

protected:
	UFUNCTION()
	void Click_Apply();

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UButton> Button_Apply;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UButton> Button_Cancel;

#pragma endregion

};