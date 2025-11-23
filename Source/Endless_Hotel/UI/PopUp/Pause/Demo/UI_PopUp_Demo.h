// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "CoreMinimal.h"
#include "UI/PopUp/Pause/UI_PopUp_Pause.h"
#include "UI_PopUp_Demo.generated.h"

UCLASS(Meta = (DisableNativeTick))
class ENDLESS_HOTEL_API UUI_PopUp_Demo : public UUI_PopUp_Pause
{
	GENERATED_BODY()
	
#pragma region Base

protected:
	virtual void NativeOnInitialized() override;

#pragma endregion

#pragma region Button

protected:
	UFUNCTION()
	void ButtonClick_Return();

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UButton> Button_Return;

#pragma endregion

#pragma region Clear

protected:
	UFUNCTION()
	void OpenDemoWidget();

protected:
	UPROPERTY()
	TSubclassOf<UUI_PopUp_Demo> UI_Demo;

#pragma endregion

};