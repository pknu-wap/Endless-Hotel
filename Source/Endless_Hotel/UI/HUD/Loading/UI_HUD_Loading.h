// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "UI/HUD/UI_HUD_Base.h"
#include <CoreMinimal.h>
#include <UI_HUD_Loading.generated.h>

UCLASS(Meta = (DisableNativeTick))
class ENDLESS_HOTEL_API UUI_HUD_Loading : public UUI_HUD_Base
{
	GENERATED_BODY()

#pragma region Show & Hide

public:
	virtual void ShowWidget() override;
	virtual void HideWidget() override;

#pragma endregion

#pragma region Loading

private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UUI_Slider_Loading> Slider_Loading;
	
#pragma endregion

#pragma region EyeEffect

public:
	void StartLoadingEyeEffect();

private:
	FTimerHandle WaitHandle;

#pragma endregion

#pragma region SandClock

public:
	void SpawnSandClock();

private:
	UPROPERTY(EditAnywhere, Category = "SandClock")
	TSubclassOf<class ASandClock> SandClockClass;

	UPROPERTY(EditAnywhere, Category = "SandClock")
	FTransform ClockSpawnTrans;

	UPROPERTY()
	TObjectPtr<class ASandClock> SandClock;

#pragma endregion

};