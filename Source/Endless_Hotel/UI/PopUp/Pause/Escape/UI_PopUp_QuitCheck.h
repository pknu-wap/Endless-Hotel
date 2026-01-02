// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "CoreMinimal.h"
#include "UI/PopUp/Pause/UI_PopUp_Pause.h"
#include "UI_PopUp_QuitCheck.generated.h"

UCLASS()
class ENDLESS_HOTEL_API UUI_PopUp_QuitCheck : public UUI_PopUp_Pause
{
	GENERATED_BODY()
	
#pragma region Base

protected:
	virtual void NativeOnInitialized() override;

#pragma endregion

#pragma region Button

protected:
	UFUNCTION()
	void Click_Yes();

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UButton> Button_Yes;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UButton> Button_No;

#pragma endregion

};