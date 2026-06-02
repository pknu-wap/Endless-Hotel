// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "UI/PopUp/UI_PopUp_Base.h"
#include <CoreMinimal.h>
#include <UI_PopUp_Demo.generated.h>

UCLASS(Meta = (DisableNativeTick))
class ENDLESS_HOTEL_API UUI_PopUp_Demo : public UUI_PopUp_Base
{
	GENERATED_BODY()
	
#pragma region Base

protected:
	virtual void NativeOnInitialized() override;

#pragma endregion

#pragma region Show

public:
	virtual void ShowWidget() override;

#pragma endregion

#pragma region Button

protected:
	UFUNCTION()
	void Click_QRCode();

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UButton> Button_Faker;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UButton> Button_Karina;

#pragma endregion

#pragma region I See Dae Ru

protected:
	UPROPERTY(EditAnywhere, Category = "Sound")
	TObjectPtr<class USoundWave> SW_ISeeDaeRu;

#pragma endregion

};