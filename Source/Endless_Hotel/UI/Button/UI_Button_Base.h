// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "CoreMinimal.h"
#include "Components/Button.h"
#include "UI_Button_Base.generated.h"

UCLASS(Meta = (DisableNativeTick))
class ENDLESS_HOTEL_API UUI_Button_Base : public UButton
{
	GENERATED_BODY()
	
#pragma region Index

public:
	uint8 GetButtonIndex() { return ButtonIndex; }

protected:
	UPROPERTY(EditAnywhere)
	uint8 ButtonIndex = 0;

#pragma endregion

#pragma region Owner

public:
	void SetButtonOwner(class UUI_Base* Owner) { ButtonOwner = Owner; }

protected:
	UPROPERTY()
	TObjectPtr<class UUI_Base> ButtonOwner;

#pragma endregion

};