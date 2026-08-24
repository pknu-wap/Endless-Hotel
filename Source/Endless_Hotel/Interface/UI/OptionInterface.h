// Copyright by 2026-1 WAP Game 2 team

#pragma once

#include "Type/UI/Type_Setting.h"
#include <CoreMinimal.h>
#include <UObject/Interface.h>
#include <OptionInterface.generated.h>

UINTERFACE(MinimalAPI)
class UOptionInterface : public UInterface
{
	GENERATED_BODY()
};

class ENDLESS_HOTEL_API IOptionInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent)
	void InitOption(EOptionCategory Category, TArray<EOptionValue> Values);
};