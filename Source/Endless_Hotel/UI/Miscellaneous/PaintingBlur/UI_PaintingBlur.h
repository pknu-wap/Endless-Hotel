// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include <CoreMinimal.h>
#include <Blueprint/UserWidget.h>
#include <UI_PaintingBlur.generated.h>

UCLASS()
class ENDLESS_HOTEL_API UUI_PaintingBlur : public UUserWidget
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
