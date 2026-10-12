// Copyright by 2026-1 WAP Game 2 team

#pragma once

#include "Actor/Interact/Read/InteractRead.h"
#include "Type/Anomaly/Type_AnomalyRule.h"
#include <CoreMinimal.h>
#include <Manual.generated.h>

UCLASS()
class ENDLESS_HOTEL_API AManual : public AInteractRead
{
	GENERATED_BODY()

#pragma region Base

public:
	AManual(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void BeginPlay() override;

#pragma endregion

#pragma region Interact

public:
	virtual void Interact(class AEHCharacter* Interacter) override;

#pragma endregion

#pragma region Component

private:
	UPROPERTY(EditAnywhere)
	TObjectPtr<USceneComponent> Comp_Root;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UStaticMeshComponent> SM_Paper;

	UPROPERTY()
	TMap<EAnomalyRule, TObjectPtr<UStaticMeshComponent>> PaperFragments;

#pragma endregion

#pragma region Rule

private:
	void ShowUnlockRulePaper();
	void OnAddedNewRule(EAnomalyRule Rule);

#pragma endregion

#pragma region Switch

public:
	void SwitchPaper();

private:
	UPROPERTY(EditAnywhere, Category = "Switch")
	FTransform MiddleTrans;
	FTransform UpTrans;
	FTransform DownTrans;

	bool bIsSwitching = false;
	bool bFirstPaper = true;

#pragma endregion

#pragma region Remind

private:
	void SetNeedRemind(EAnomalyRule Rule) { bNeedRemind = true; }
	void RemindManual();

private:
	bool bNeedRemind = false;

#pragma endregion

};