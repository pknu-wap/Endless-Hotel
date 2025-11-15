// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "CoreMinimal.h"
#include "Delegates/DelegateCombinations.h"
#include "UI/Button/UI_Button_Base.h"
#include "UI_Button_Text.generated.h"

#pragma region Declare

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FHoverEvent, uint8, Index);

#pragma endregion

UCLASS(Meta = (DisableNativeTick))
class ENDLESS_HOTEL_API UUI_Button_Text : public UUI_Button_Base
{
	GENERATED_BODY()
	
#pragma region Base

public:
	UUI_Button_Text();

#pragma endregion

#pragma region Button

protected:
	UFUNCTION()
	void OnButtonClicked();

	UFUNCTION()
	void OnButtonHovered();

	UFUNCTION()
	void OnButtonUnhovered(uint8 Index);

protected:
	// 언리얼 폰트 DPI = 96, Figma 폰트 DPI = 72
	// 해당 DPI 차이를 극복하기 위한 방법 ㅠㅠ -> 프로젝트 세팅으로 변경해도 C++에서는 적용 X
	const float FontAdjustValue = 72.0f / 96.0f;

	const float ButtonSize_Hover = 48;
	const float ButtonSize_Normal = 32;

	UPROPERTY(EditAnywhere)
	TObjectPtr<class UTexture2D> Texture_Button_Normal;

	UPROPERTY(EditAnywhere)
	TObjectPtr<class UTexture2D> Texture_Button_Hover;

	FHoverEvent HoverEvent;

	UPROPERTY(EditAnywhere)
	uint8 ButtonIndex = 0;

#pragma endregion

};