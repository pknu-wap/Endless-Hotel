// Copyright by 2026-1 WAP Game 2 team

#pragma once

#include "UI/PopUp/UI_PopUp_Base.h"
#include <CoreMinimal.h>
#include <UI_PopUp_NoteBookZoomIn.generated.h>

UCLASS(Meta = (DisableNativeTick))
class ENDLESS_HOTEL_API UUI_PopUp_NoteBookZoomIn : public UUI_PopUp_Base
{
	GENERATED_BODY()
	
#pragma region Base

protected:
	virtual void NativeOnInitialized() override;

#pragma endregion

#pragma region Description

public:
	void SetDescription(uint8 Index);

private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UImage> Image_Picture;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> Text_Description;

#pragma endregion

#pragma region Button

private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UButton> Button_ESC;

#pragma endregion

};