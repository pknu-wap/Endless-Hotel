// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "Type/UI/Type_UI.h"
#include <CoreMinimal.h>
#include <Subsystems/GameInstanceSubsystem.h>
#include <UI_Controller.generated.h>

UCLASS()
class ENDLESS_HOTEL_API UUI_Controller : public UGameInstanceSubsystem
{
	GENERATED_BODY()

#pragma region Base

public:
	UUI_Controller();

#pragma endregion

#pragma region Open & Close

public:
	UUI_Base* OpenWidget(TSubclassOf<class UUI_Base> WidgetClass);
	void CloseWidget();
	void ClearAllWidget();

protected:
	void SetInputMode(const EInputModeType& InputMode);

protected:
	void AdjustZOrder(bool bUp);

public:
	UUI_Base* GetCurrentBaseWidget() { return PopUpWidgets[0]; }
	UUI_Base* GetCurrentPopUpWidget() { return PopUpWidgets.Top(); }

protected:
	UPROPERTY()
	TArray<TObjectPtr<class UUI_Base>> PopUpWidgets;

	const int32 Max_ZOrder = 100;
	const int32 Min_ZOrder = 0;

	int32 Widget_ZOrder = 0;

#pragma endregion

#pragma region Widget

public:
	void OpenMapBaseWidget();

protected:
	UPROPERTY()
	TSubclassOf<class UUI_Base> UI_MainMenu;

	UPROPERTY()
	TSubclassOf<class UUI_Base> UI_InGame;

#pragma endregion

};