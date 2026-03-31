// Copyright by 2026-1 WAP Game 2 team

#pragma once

#include "UI/PopUp/UI_PopUp_Base.h"
#include <CoreMinimal.h>
#include <UI_PopUp_Read.generated.h>

UCLASS(Meta = (DisableNativeTick))
class ENDLESS_HOTEL_API UUI_PopUp_Read : public UUI_PopUp_Base
{
	GENERATED_BODY()
	
#pragma region Input

protected:
	virtual void Input_ESC() override;

#pragma endregion

#pragma region Target

public:
	void SetTarget(AActor* Target) { TargetObject = Target; }

protected:
	UPROPERTY()
	TWeakObjectPtr<AActor> TargetObject;

#pragma endregion

};