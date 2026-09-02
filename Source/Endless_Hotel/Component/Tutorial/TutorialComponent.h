// Copyright by 2026-1 WAP Game 2 team

#pragma once

#include "Component/EHComponent.h"
#include "Type/Save/Type_Save.h"
#include <CoreMinimal.h>
#include <TutorialComponent.generated.h>

UCLASS(meta = (BlueprintSpawnableComponent))
class ENDLESS_HOTEL_API UTutorialComponent : public UEHComponent
{
	GENERATED_BODY()
	
#pragma region Base

protected:
	virtual void BeginPlay() override;

#pragma endregion

#pragma region Widget

public:
	void ShowTutorialWidget();
	void HideTutorialWidget();

public:
	bool bIsCheckTutorial = false;

private:
	UPROPERTY(EditAnywhere, Category = "Widget")
	FText TargetKey;

	UPROPERTY(EditAnywhere, Category = "Widget")
	FText TargetDescription;

	UPROPERTY(EditAnywhere, Category = "Widget")
	float WidgetDuration = 10.f;

	UPROPERTY(EditAnywhere, Category = "Widget")
	EGameProgression TargetProgression = EGameProgression::Tutorial;

	UPROPERTY()
	TWeakObjectPtr<class UInteractComponent> Comp_Interact;

	UPROPERTY()
	TWeakObjectPtr<class UUI_Tutorial> UI_Tutorial;

#pragma endregion

#pragma region Trigger

private:
	UFUNCTION()
	void OnTriggerBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OverlappedComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:
	UPROPERTY()
	TObjectPtr<class UBoxComponent> TriggerBox;

	UPROPERTY(EditAnywhere, Category = "Trigger")
	FTransform TriggerTrans;

#pragma endregion

};