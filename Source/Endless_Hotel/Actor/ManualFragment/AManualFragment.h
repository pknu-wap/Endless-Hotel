// Copyright by 2026-1 WAP Game 2 team

#pragma once

#include "Actor/Interact/InteractBase.h"
#include "Type/Anomaly/Type_AnomalyRule.h"
#include "Type/Anomaly/Type_AnomalyID.h"
#include <CoreMinimal.h>
#include <AManualFragment.generated.h>

UCLASS()
class ENDLESS_HOTEL_API AManualFragment : public AInteractBase
{
	GENERATED_BODY()

#pragma region Base

public:
	AManualFragment(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void BeginPlay() override;

#pragma endregion

#pragma region UI

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI")
	TObjectPtr<class UWidgetComponent> Component_ManualWidget;

#pragma endregion

#pragma region RuleSetting

protected:
	UPROPERTY(EditAnywhere, Category = "RuleSetting|Rule")
	EAnomalyRule Rule;

	UPROPERTY(EditAnywhere, Category = "RuleSetting|BoundAnomaly")
	EAnomalyID BoundAnomaly;

	UPROPERTY(EditAnywhere, Category = "RuleSetting|Placement")
	FTransform Placement;

protected:
	UFUNCTION()
	void SetManualFragment();

#pragma endregion

#pragma region Interact

public:
	virtual void Interact_Implementation(AEHCharacter* Interacter) override;

#pragma endregion
};