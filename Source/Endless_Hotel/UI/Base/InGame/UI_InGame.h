// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "CoreMinimal.h"
#include "UI/UI_Base.h"
#include "UI_InGame.generated.h"

UCLASS(Meta = (DisableNativeTick))
class ENDLESS_HOTEL_API UUI_InGame : public UUI_Base
{
	GENERATED_BODY()
	
#pragma region Crosshair

protected:
	UFUNCTION()
	void ChangeCrosshair(bool bCanInteract);
	
protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UImage> Crosshair;

	UPROPERTY(EditAnywhere)
	TObjectPtr<class UTexture2D> Crosshair_Normal;

	UPROPERTY(EditAnywhere)
	TObjectPtr<class UTexture2D> Crosshair_Interact;

#pragma endregion

};