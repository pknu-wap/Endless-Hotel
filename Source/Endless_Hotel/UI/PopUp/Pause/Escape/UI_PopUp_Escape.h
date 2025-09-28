// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "CoreMinimal.h"
#include "UI/PopUp/Pause/UI_PopUp_Pause.h"
#include "UI_PopUp_Escape.generated.h"

UCLASS()
class ENDLESS_HOTEL_API UUI_PopUp_Escape : public UUI_PopUp_Pause
{
	GENERATED_BODY()

#pragma region Base

protected:
	virtual void NativeOnInitialized() override;

#pragma endregion

#pragma region Button

protected:
	UFUNCTION()
	void ButtonClick_MainMenu();

	UFUNCTION()
	void ButtonClick_Quit();

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UButton> ResumeButton;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UButton> MainMenuButton;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UButton> QuitButton;

#pragma endregion

};