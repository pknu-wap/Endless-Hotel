// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "UI/World/UI_World_Base.h"
#include <CoreMinimal.h>
#include <UI_Interact.generated.h>

UCLASS(Meta = (DisableNativeTick))
class ENDLESS_HOTEL_API UUI_Interact : public UUI_World_Base
{
	GENERATED_BODY()

#pragma region Base

protected:
	virtual void NativeOnInitialized() override;

#pragma endregion

#pragma region Description

public:
	void SetDescription(FText Value);
	void ShowDescription(bool bIsShow);

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UImage> Image_Key_E;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> Text_Description;

#pragma endregion

};