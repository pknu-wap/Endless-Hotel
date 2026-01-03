// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "Type/Sound/Type_Sound.h"
#include <CoreMinimal.h>
#include <Subsystems/GameInstanceSubsystem.h>
#include <SoundController.generated.h>

UCLASS()
class ENDLESS_HOTEL_API USoundController : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
#pragma region Base

protected:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

#pragma endregion

#pragma region SoundClass

public:
	float GetSoundClassValue(const ESoundClassType& Type);
	void SetSoundClassValue(const ESoundClassType& Type, float Value);

protected:
	UPROPERTY()
	TObjectPtr<class USoundClass> SC_Master;

	UPROPERTY()
	TObjectPtr<class USoundClass> SC_BGM;

	UPROPERTY()
	TObjectPtr<class USoundClass> SC_SFX;

	UPROPERTY()
	TObjectPtr<class USoundClass> SC_UI;

	UPROPERTY()
	TObjectPtr<class USoundClass> SC_Voice;

protected:
	const uint8 Index_BGM = 0;
	const uint8 Index_SFX = 1;
	const uint8 Index_UI = 2;
	const uint8 Index_Voice = 3;

#pragma endregion

#pragma region Fade In & Out

public:
	void FadeSFXSound(bool bIsOpen);

protected:
	UPROPERTY()
	TObjectPtr<class USoundMix> SCM_SFX_Mute;

	UPROPERTY()
	TObjectPtr<class USoundMix> SCM_SFX_Fade;

#pragma endregion

};