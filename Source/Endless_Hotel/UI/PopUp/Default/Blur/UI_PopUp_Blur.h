// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "CoreMinimal.h"
#include "UI/PopUp/Default/UI_PopUp_Default.h"
#include "UI_PopUp_Blur.generated.h"

UCLASS(Meta = (DisableNativeTick))
class ENDLESS_HOTEL_API UUI_PopUp_Blur : public UUI_PopUp_Default
{
	GENERATED_BODY()
	
#pragma region Base

protected:
	virtual void NativeConstruct() override;

#pragma endregion

#pragma region Blur

protected:
	void StartSightBlur();

protected:
	FTimerHandle BlurHandle;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UBackgroundBlur> BackBlur;

#pragma endregion

};