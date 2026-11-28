// Copyright by 2026-1 WAP Game 2 team

#pragma once

#include "UI/PopUp/UI_PopUp_Base.h"
#include <CoreMinimal.h>
#include <UI_PopUp_Credit_True.generated.h>

UCLASS()
class ENDLESS_HOTEL_API UUI_PopUp_Credit_True : public UUI_PopUp_Base
{
	GENERATED_BODY()

#pragma region Show

public:
	virtual void ShowWidget() override;

#pragma endregion

#pragma region Credit

private:
	UFUNCTION()
	void OnFinishedAnimation();

private:
	UPROPERTY(EditDefaultsOnly, Category = "Credit")
	TObjectPtr<class ULevelSequence> LS_Ending;

	UPROPERTY(Transient, meta = (BindWidgetAnim))
	TObjectPtr<UWidgetAnimation> WA_Credit;

#pragma endregion

};