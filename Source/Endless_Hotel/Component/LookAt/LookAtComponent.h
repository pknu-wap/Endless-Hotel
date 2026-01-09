// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "Component/EHComponent.h"
#include <CoreMinimal.h>
#include <LookAtComponent.generated.h>

UCLASS()
class ENDLESS_HOTEL_API ULookAtComponent : public UEHComponent
{
	GENERATED_BODY()
	
#pragma region Base

public:
	ULookAtComponent(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

#pragma endregion

#pragma region Setting

public:
	void SettingWidgetComponent(class UWidgetComponent* Comp) { WC = Comp; }

protected:
	UPROPERTY()
	TObjectPtr<class UWidgetComponent> WC;

#pragma endregion

#pragma region LookAt

protected:
	void LookAtPlayer();

#pragma endregion

};