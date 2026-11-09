// Copyright by 2026-1 WAP Game 2 team

#pragma once

#include "UI/PopUp/UI_PopUp_Base.h"
#include <CoreMinimal.h>
#include <UI_PopUp_Credit_Bad.generated.h>

UCLASS()
class ENDLESS_HOTEL_API UUI_PopUp_Credit_Bad : public UUI_PopUp_Base
{
	GENERATED_BODY()
	
#pragma region Active

public:
	virtual void ActiveWidget() override;

#pragma endregion

#pragma region Show

public:
	virtual void ShowWidget() override;

#pragma endregion

#pragma region Credit

private:
	UFUNCTION()
	void OnFinishedAnimation();

private:
	UPROPERTY(Transient, meta = (BindWidgetAnim))
	TObjectPtr<UWidgetAnimation> WA_ShowLogo;

	UPROPERTY(EditDefaultsOnly, Category = "Logo")
	TObjectPtr<USoundWave> SW_CreditStart;

	UPROPERTY()
	TArray<TObjectPtr<class UUI_NoteBook>> UI_Pictures;

#pragma endregion

};