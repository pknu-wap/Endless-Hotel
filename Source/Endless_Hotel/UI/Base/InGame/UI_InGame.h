// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "CoreMinimal.h"
#include "UI/UI_Base.h"
#include "UI_InGame.generated.h"

UCLASS(Meta = (DisableNativeTick))
class ENDLESS_HOTEL_API UUI_InGame : public UUI_Base
{
	GENERATED_BODY()
	
#pragma region Base

protected:
	virtual void NativeOnInitialized() override;
	virtual void NativeConstruct() override;

#pragma endregion

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

#pragma region Brightness

protected:
	void SetBrightness();

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UImage> Image_Brightness;

#pragma endregion

#pragma region Demo

protected:
	UFUNCTION()
	void OpenDemoWidget();

protected:
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUI_Base> UI_Demo;

#pragma endregion

};