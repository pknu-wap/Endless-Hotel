// Copyright by 2026-1 WAP Game 2 team

#pragma once

#include "Component/EHComponent.h"
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

private:
	void ShowTutorialWidget();
	void DisappearTutorialWidget();

protected:
	UPROPERTY(EditAnywhere, Category = "Widget")
	FText TargetKey;

	UPROPERTY(EditAnywhere, Category = "Widget")
	FText TargetDescription;

	UPROPERTY(EditAnywhere, Category = "Widget")
	float WidgetDuration = 10.f;

private:
	UPROPERTY()
	TWeakObjectPtr<class UWidgetComponent> Comp_Widget;

#pragma endregion

#pragma region Trigger

private:
	UFUNCTION()
	void OnTriggerBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OverlappedComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

protected:
	UPROPERTY()
	TObjectPtr<class UBoxComponent> TriggerBox;

	UPROPERTY(EditAnywhere, Category = "Trigger")
	FTransform TriggerTrans;

#pragma endregion

};