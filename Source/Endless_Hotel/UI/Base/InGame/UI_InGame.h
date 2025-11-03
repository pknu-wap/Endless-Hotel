// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "CoreMinimal.h"
#include "UI/UI_Base.h"
#include "Delegates/DelegateCombinations.h"
#include "UI_InGame.generated.h"

#pragma region Declare

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCanInteract, bool, CanInteract);

#pragma endregion

UCLASS(Meta = (DisableNativeTick))
class ENDLESS_HOTEL_API UUI_InGame : public UUI_Base
{
	GENERATED_BODY()
	
#pragma region Base

protected:
	virtual void NativeOnInitialized() override;

#pragma endregion

#pragma region Crosshair

protected:
	UFUNCTION()
	void ChangeCrosshair(bool bCanInteract);

public:
	static FCanInteract CanInteract;
	
protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UImage> Crosshair;

	UPROPERTY(EditAnywhere)
	TObjectPtr<class UTexture2D> Crosshair_Normal;

	UPROPERTY(EditAnywhere)
	TObjectPtr<class UTexture2D> Crosshair_Interact;

#pragma endregion

};