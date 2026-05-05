// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "UI/Slider/UI_Slider_Base.h"
#include <CoreMinimal.h>
#include <UI_Slider_Loading.generated.h>

UCLASS()
class ENDLESS_HOTEL_API UUI_Slider_Loading : public UUI_Slider_Base
{
	GENERATED_BODY()
	
#pragma region Base

protected:
	virtual void NativeOnInitialized() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

private:
	UPROPERTY()
	TWeakObjectPtr<class UEHGameInstance> GameInstance;

#pragma endregion

#pragma region Loading

public:
	bool IsLoadingComplete() { return LoadingPercentage >= TargetPercentage; }

private:
	void SetLoadingPercentage(float InDeltaTime);

private:
	const float TargetPercentage = 1.f;
	float LoadingPercentage = 0.f;

#pragma endregion

};