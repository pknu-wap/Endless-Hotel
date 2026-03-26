// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "Type/UI/Type_UI_Widget.h"
#include <CoreMinimal.h>
#include <Subsystems/GameInstanceSubsystem.h>
#include <UI_Controller.generated.h>

UCLASS()
class ENDLESS_HOTEL_API UUI_Controller : public UGameInstanceSubsystem
{
	GENERATED_BODY()

#pragma region Open & Close

public:
	class UUI_Base* OpenWidget(TSubclassOf<class UUI_Base> WidgetClass);
	void CloseWidget();
	void ClearAllWidget();

public:
	class UUI_Base* GetCurrentHUDWidget() { return PopUpWidgets[0]; }
	class UUI_Base* GetCurrentPopUpWidget() { return PopUpWidgets.Top(); }

protected:
	UPROPERTY()
	TArray<TObjectPtr<class UUI_Base>> PopUpWidgets;

#pragma endregion

#pragma region Input

protected:
	void SetInputMode(const EInputModeType& InputMode);

#pragma endregion

#pragma region ZOrder

protected:
	void AdjustZOrder(bool bUp);

protected:
	const int32 Max_ZOrder = 100;
	const int32 Min_ZOrder = 0;

	int32 Widget_ZOrder = 0;

#pragma endregion

};