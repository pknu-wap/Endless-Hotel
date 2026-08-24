// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include <CoreMinimal.h>
#include <Blueprint/UserWidget.h>
#include <Delegates/DelegateCombinations.h>
#include <UI_Base.generated.h>

UCLASS(Abstract, Meta = (DisableNativeTick))
class ENDLESS_HOTEL_API UUI_Base : public UUserWidget
{
	GENERATED_BODY()

#pragma region Base

protected:
	virtual void NativeOnInitialized() override;
	virtual void NativeConstruct() override;

#pragma endregion

#pragma region Active

public:
	virtual void ActiveWidget() {}
	virtual void DeactiveWidget() { SetVisibility(ESlateVisibility::Collapsed); }

#pragma endregion

#pragma region Show & Hide

public:
	virtual void ShowWidget() { SetVisibility(ESlateVisibility::SelfHitTestInvisible); }
	virtual void HideWidget(){ SetVisibility(ESlateVisibility::Hidden); }

#pragma endregion

};