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
	virtual void InitOption(EOptionCategory Category, TArray<FOptionValuePair> Values) PURE_VIRTUAL(ThisClass::InitOption, );
};