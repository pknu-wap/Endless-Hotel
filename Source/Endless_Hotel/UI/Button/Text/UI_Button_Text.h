// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "CoreMinimal.h"
#include "UI/Button/UI_Button_Base.h"
#include "UI_Button_Text.generated.h"

UCLASS(Meta = (DisableNativeTick))
class ENDLESS_HOTEL_API UUI_Button_Text : public UUI_Button_Base
{
	GENERATED_BODY()
	
#pragma region Base

protected:
	virtual TSharedRef<SWidget, ESPMode::ThreadSafe> RebuildWidget() override;

#pragma endregion

#pragma region Button

protected:
	UFUNCTION()
	void OnButtonClicked();

	UFUNCTION()
	void OnButtonHovered();

	UFUNCTION()
	void OnButtonUnhovered();

protected:
	// 언리얼 폰트 DPI = 96, Figma 폰트 DPI = 72
	// 해당 DPI 차이를 극복하기 위한 방법 ㅠㅠ -> 프로젝트 세팅으로 변경해도 C++에서는 적용 X
	const float FontAdjustValue = 72.0f / 96.0f;

#pragma endregion

};