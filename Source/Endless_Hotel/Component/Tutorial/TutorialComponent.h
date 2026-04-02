// Copyright by 2026-1 WAP Game 2 team

#pragma once

#include "Component/EHComponent.h"
#include <CoreMinimal.h>
#include <TutorialComponent.generated.h>

UCLASS()
class ENDLESS_HOTEL_API UTutorialComponent : public UEHComponent
{
	GENERATED_BODY()
	
#pragma region Base

protected:
	virtual void BeginPlay() override;

#pragma endregion

#pragma region Widget

private:
	void ShowTutorialWidget();
	void DisappearTutorialWidget();

protected:
	UPROPERTY(EditAnywhere, Category = "Widget")
	FText TargetName;

private:
	UPROPERTY()
	TWeakObjectPtr<class UWidgetComponent> Comp_Widget;

	UPROPERTY()
	TSubclassOf<class UUserWidget> UI_Tutorial_Class;

#pragma endregion

};