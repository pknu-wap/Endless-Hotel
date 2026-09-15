// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "UI/UI_Base.h"
#include <CoreMinimal.h>
#include <UI_Interact.generated.h>

UCLASS(Meta = (DisableNativeTick))
class ENDLESS_HOTEL_API UUI_Interact : public UUI_Base
{
	GENERATED_BODY()

#pragma region Base

protected:
	virtual void NativeOnInitialized() override;

#pragma endregion

#pragma region Description

public:
	void SetDescription(FText Value);
	void ShowDescription(bool bIsShow, bool bNeedArrow);

private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> Text_Description;

#pragma endregion

#pragma region Animation

public:
	void PlayChangeAnimation(bool bUp);

private:
	UPROPERTY(meta = (BindWidgetAnim), Transient)
	TObjectPtr<UWidgetAnimation> Anim_Left;

	UPROPERTY(meta = (BindWidgetAnim), Transient)
	TObjectPtr<UWidgetAnimation> Anim_Right;

#pragma endregion

#pragma region Arrow

private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UImage> Image_Left;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UImage> Image_Right;

#pragma endregion

};