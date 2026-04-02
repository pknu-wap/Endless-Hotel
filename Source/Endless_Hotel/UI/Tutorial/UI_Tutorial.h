// Copyright by 2026-1 WAP Game 2 team

#pragma once

#include "UI/UI_Base.h"
#include <CoreMinimal.h>
#include <UI_Tutorial.generated.h>

UCLASS(Meta = (DisableNativeTick))
class ENDLESS_HOTEL_API UUI_Tutorial : public UUI_Base
{
	GENERATED_BODY()
	
#pragma region Text

public:
	void SetTargetName(const FText& Name);

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> Text_TargetName;

#pragma endregion

};