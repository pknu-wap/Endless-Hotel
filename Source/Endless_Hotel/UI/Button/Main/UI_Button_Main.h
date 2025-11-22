// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "CoreMinimal.h"
#include "UI/Button/UI_Button_Base.h"
#include "UI_Button_Main.generated.h"

UCLASS(Meta = (DisableNativeTick))
class ENDLESS_HOTEL_API UUI_Button_Main : public UUI_Button_Base
{
	GENERATED_BODY()
	
#pragma region Base

protected:
	virtual void SynchronizeProperties() override;

#pragma endregion

#pragma region Button

public:
	uint8 GetButtonIndex() { return ButtonIndex; }

	void ResetButton();

protected:
	UFUNCTION()
	void OnButtonHover();

protected:
	void SetButtonSize(const float& ButtonSize);
	void SetButtonTexture(class UTexture2D* ButtonTexture);
	void SetFontSize(const uint8& FontSize);

protected:
	UPROPERTY(EditAnywhere)
	TObjectPtr<class UTexture2D> Texture_Button_Normal;

	UPROPERTY(EditAnywhere)
	TObjectPtr<class UTexture2D> Texture_Button_Hover;

protected:
	// 언리얼 폰트 DPI = 96, Figma 폰트 DPI = 72
	// 해당 DPI 차이를 극복하기 위한 방법 ㅠㅠ -> 프로젝트 세팅으로 변경해도 C++에서는 적용 X
	const float FontAdjustValue = 72.0f / 96.0f;

	const float ButtonSize_Normal = 32;
	const float ButtonSize_Hover = 48;

	const uint8 FontSize_Normal = 48;
	const uint8 FontSize_Hover = 64;

#pragma endregion

};