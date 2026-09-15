// Copyright by 2026-1 WAP Game 2 team

#pragma once

#include "UI/PopUp/UI_PopUp_Base.h"
#include <CoreMinimal.h>
#include <UI_PopUp_Acquire.generated.h>

UCLASS(Meta = (DisableNativeTick))
class ENDLESS_HOTEL_API UUI_PopUp_Acquire : public UUI_PopUp_Base
{
	GENERATED_BODY()

#pragma region Base

protected:
	virtual void NativeOnInitialized() override;

#pragma endregion

#pragma region Item

public:
	void SetAcquireItem(AActor* Acquire) { Item = Acquire; }

private:
	UPROPERTY()
	TWeakObjectPtr<AActor> Item;

#pragma endregion

#pragma region Input

protected:
	virtual void Input_ESC() override;

private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UButton> Button_ESC;

#pragma endregion

#pragma region Info

public:
	void SetInfoText(FText Info);

private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> Text_Info;

#pragma endregion

};