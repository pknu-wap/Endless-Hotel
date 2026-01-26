// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include <CoreMinimal.h>
#include <Components/Button.h>
#include <UI_Button_Base.generated.h>

UCLASS(Meta = (DisableNativeTick))
class ENDLESS_HOTEL_API UUI_Button_Base : public UButton
{
	GENERATED_BODY()

#pragma region Base

protected:
	virtual void SynchronizeProperties() override;

#pragma endregion

#pragma region Owner

private:
	void SetWidgetOwner();

protected:
	UPROPERTY()
	TWeakObjectPtr<class UUI_Base> Owner;

#pragma endregion

};