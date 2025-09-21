// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "UI_Controller.generated.h"

#pragma region Declare

#define BASE_UI_ZORDER 0
#define POPUP_UI_ZORDER 1

UENUM(BlueprintType)
enum class EInputModeType : uint8
{
	GameOnly	UMETA(DisplayName = "GameOnly"),
	UIOnly		UMETA(DisplayName = "UIOnly"),
	GameAndUI	UMETA(DisplayName = "GameAndUI")
};

#pragma endregion

UCLASS()
class ENDLESS_HOTEL_API UUI_Controller : public UGameInstanceSubsystem
{
	GENERATED_BODY()

#pragma region Widget

public:
	class UUI_Base* OpenBaseWidget(TSubclassOf<class UUI_Base> WidgetClass, const EInputModeType& InputMode = EInputModeType::UIOnly);
	class UUI_PopUp_Base* OpenPopUpWidget(TSubclassOf<class UUI_PopUp_Base> WidgetClass, const EInputModeType& InputMode = EInputModeType::UIOnly);
	class UUI_PopUp_Base* OpenStrongPopUpWidget(TSubclassOf<class UUI_PopUp_Base> WidgetClass, const EInputModeType& InputMode = EInputModeType::UIOnly);

	void CloseBaseWidget(const EInputModeType& InputMode = EInputModeType::GameOnly);
	void ClosePopUpWidget(const EInputModeType& InputMode = EInputModeType::GameOnly);
	void CloseStrongPopUpWidget(const EInputModeType& InputMode = EInputModeType::GameOnly);

	class UUI_Base* GetCurrentBaseWidget() { return BaseWidget; }
	class UUI_PopUp_Base* GetCurrentPopUpWidget() { return PopUpWidget; }

protected:
	void SetInputMode(const EInputModeType& InputMode);

protected:
	UPROPERTY()
	TObjectPtr<class UUI_Base> BaseWidget;

	UPROPERTY()
	TObjectPtr<class UUI_PopUp_Base> PopUpWidget;

#pragma endregion

};