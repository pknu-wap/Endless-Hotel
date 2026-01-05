// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "UI/PopUp/UI_PopUp_Base.h"
#include <CoreMinimal.h>
#include <UI_PopUp_PaintingBlur.generated.h>

UCLASS()
class ENDLESS_HOTEL_API UUI_PopUp_PaintingBlur : public UUI_PopUp_Base
{
	GENERATED_BODY()

#pragma region Blur

public:
	void StartPaintingBlur();

protected:
	FTimerHandle BlurHandle;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UBackgroundBlur> BackBlur;

#pragma endregion

};
