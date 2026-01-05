// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "UI/PopUp/UI_PopUp_Base.h"
#include <CoreMinimal.h>
#include <UI_PopUp_Compendium.generated.h>

UCLASS(Meta = (DisableNativeTick))
class ENDLESS_HOTEL_API UUI_PopUp_Compendium : public UUI_PopUp_Base
{
	GENERATED_BODY()
	
#pragma region Base

protected:
	virtual void NativeOnInitialized() override;

#pragma endregion

#pragma region Button

protected:
	UFUNCTION()
	void Click_Previous();

	UFUNCTION()
	void Click_Next();

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UButton> Button_Previous;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UButton> Button_Next;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UButton> Button_Close;

#pragma endregion

#pragma region Widget

protected:
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUI_Base> UI_Previous;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUI_Base> UI_Next;

	UPROPERTY(EditAnywhere)
	int32 Page_Left;

	UPROPERTY(EditAnywhere)
	int32 Page_Right;

#pragma endregion

#pragma region Box

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UVerticalBox> Box_Left;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UVerticalBox> Box_Right;

#pragma endregion

};