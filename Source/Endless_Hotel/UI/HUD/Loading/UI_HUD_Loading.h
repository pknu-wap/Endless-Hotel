// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "Type/Level/Type_Level.h"
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

public:
	bool IsLoadingCompleted();

private:
	void OnPossessedCamera();

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UUI_Slider_Loading> Slider_Loading;

private:
	FTimerHandle PossessHandle;
	
#pragma endregion

#pragma region EyeEffect

public:
	void StartLoadingEyeEffect();
	bool IsCompletedEyeEffect() { return bIsCompletedEyeEffect; }

private:
	void WaitEyeEffect();

private:
	FTimerHandle WaitHandle;
	bool bIsCompletedEyeEffect = false;

#pragma endregion

#pragma region SandClock

protected:
	UPROPERTY(EditAnywhere, Category = "SandClock")
	TSubclassOf<class ASandClock> SandClockClass;

	UPROPERTY(EditAnywhere, Category = "SandClock")
	FTransform ClockSpawnTrans;

private:
	UPROPERTY()
	TObjectPtr<class ASandClock> SandClock;

#pragma endregion

};