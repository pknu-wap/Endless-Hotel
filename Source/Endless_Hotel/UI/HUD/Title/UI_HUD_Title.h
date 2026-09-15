// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "UI/HUD/UI_HUD_Base.h"
#include <CoreMinimal.h>
#include <UI_HUD_Title.generated.h>

UCLASS(Meta = (DisableNativeTick))
class ENDLESS_HOTEL_API UUI_HUD_Title : public UUI_HUD_Base
{
	GENERATED_BODY()

#pragma region Active

public:
	virtual void ActiveWidget() override;

#pragma endregion

#pragma region Show

public:
	virtual void ShowWidget() override;

#pragma endregion

#pragma region Logo

private:
	void SetLogoImage();

private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UImage> Image_Logo;

	UPROPERTY(EditDefaultsOnly, Category = "Logo")
	TObjectPtr<class UTexture2D> Texture_NoClear;

	UPROPERTY(EditDefaultsOnly, Category = "Logo")
	TObjectPtr<class UTexture2D> Texture_Clear;

#pragma endregion

#pragma region BGM

public:
	void StopBGM(float Duration);

private:
	UFUNCTION()
	void PlayBGM();

private:
	UPROPERTY(Transient)
	TObjectPtr<class UAudioComponent> AC;

	UPROPERTY(EditDefaultsOnly, Category = "Sound")
	TObjectPtr<class USoundWave> SW_BGM;

#pragma endregion

};