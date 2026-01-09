// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include <CoreMinimal.h>
#include <UObject/Interface.h>
#include <Interactable.generated.h>

UINTERFACE(MinimalAPI)
class UInteractable : public UInterface
{
	GENERATED_BODY()
};

class ENDLESS_HOTEL_API IInteractable
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent)
	void Interacted();
	
	UFUNCTION(BlueprintNativeEvent)
	void ShowInteractWidget(bool bIsShow);
};