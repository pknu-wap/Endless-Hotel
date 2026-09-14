// Copyright by 2026-1 WAP Game 2 team

#pragma once

#include "UI/Button/UI_Button_Base.h"
#include <CoreMinimal.h>
#include <UI_Button_NoteBook.generated.h>

UCLASS(Meta = (DisableNativeTick))
class ENDLESS_HOTEL_API UUI_Button_NoteBook : public UUI_Button_Base
{
	GENERATED_BODY()
	
#pragma region Base

protected:
	virtual void NativeOnInitialized() override;

#pragma endregion

#pragma region Index

public:
	uint8 ButtonIndex = 0;

#pragma endregion

#pragma region Click

private:
	UFUNCTION()
	void Click_Button();

#pragma endregion

};