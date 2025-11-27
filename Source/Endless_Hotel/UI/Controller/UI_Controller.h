// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "UI_Controller.generated.h"

#pragma region Declare

class UUI_Base;

UENUM(BlueprintType)
enum class EWidgetType : uint8
{
	Base			UMETA(DisplayName = "BaseWidget"),
	PopUp			UMETA(DisplayName = "PopUp")
};

UENUM(BlueprintType)
enum class EInputModeType : uint8
{
	GameOnly	UMETA(DisplayName = "GameOnly"),
	UIOnly		UMETA(DisplayName = "UIOnly"),
	GameAndUI	UMETA(DisplayName = "GameAndUI")
};

USTRUCT(BlueprintType)
struct FPopUpWidget
{
	GENERATED_BODY()

	EWidgetType WidgetType;
	EInputModeType InputModeType;
	TObjectPtr<UUI_Base> PopUpWidget;

	bool operator==(const FPopUpWidget& Widget)
	{
		return PopUpWidget == Widget.PopUpWidget;
	}
};

#pragma endregion

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
	UUI_Base* OpenWidget(TSubclassOf<UUI_Base> WidgetClass, const EWidgetType& WidgetType, const EInputModeType& InputMode);
	void CloseWidget();

public:
	void ClearAllWidget();

protected:
	void SetInputMode(const EInputModeType& InputMode);

protected:
	void AdjustZOrder(bool bUp);

protected:
	UPROPERTY()
	TArray<FPopUpWidget> PopUpWidgets;

	int32 Widget_ZOrder = 0;

public:
	UUI_Base* GetCurrentBaseWidget() { return PopUpWidgets[0].PopUpWidget; }
	UUI_Base* GetCurrentPopUpWidget() { return PopUpWidgets[Widget_ZOrder].PopUpWidget; }

#pragma endregion

#pragma region Widget

public:
	void OpenMapBaseWidget();

protected:
	UPROPERTY()
	TSubclassOf<UUI_Base> UI_MainMenu;

	UPROPERTY()
	TSubclassOf<UUI_Base> UI_InGame;

#pragma endregion

};