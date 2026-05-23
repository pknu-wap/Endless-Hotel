// Copyright by 2026-1 WAP Game 2 team

#pragma once

#include "UI/PopUp/UI_PopUp_Base.h"
#include <CoreMinimal.h>
#include <UI_PopUp_Tutorial.generated.h>

UCLASS()
class ENDLESS_HOTEL_API UUI_PopUp_Tutorial : public UUI_PopUp_Base
{
	GENERATED_BODY()
	
#pragma region Base

protected:
	virtual void NativeOnInitialized() override;

#pragma endregion

#pragma region Tutorial

private:
	UFUNCTION()
	void OpenTutorialWidget(const ELevelType& LevelType);

#pragma endregion

};