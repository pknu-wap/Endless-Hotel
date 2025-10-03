﻿// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "CoreMinimal.h"
#include "UI/PopUp/Default/UI_PopUp_Default.h"
#include "UI_PopUp_Compendium.generated.h"

UCLASS(Meta = (DisableNativeTick))
class ENDLESS_HOTEL_API UUI_PopUp_Compendium : public UUI_PopUp_Default
{
	GENERATED_BODY()
	
#pragma region Base

protected:
	virtual void NativeConstruct() override;

#pragma endregion

};