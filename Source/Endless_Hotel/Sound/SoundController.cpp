// Copyright by 2025-2 WAP Game 2 team

#include "Sound/SoundController.h"
#include <Sound/SoundMix.h>
#include <Sound/SoundClass.h>
#include <Kismet/GameplayStatics.h>

#pragma region Base

void USoundController::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	SCM_SFX_Mute = LoadObject<USoundMix>(nullptr, TEXT("/Game/EndlessHotel/Sound/SoundClass/SCM_SFX_Mute.SCM_SFX_Mute"));
	SCM_SFX_Fade = LoadObject<USoundMix>(nullptr, TEXT("/Game/EndlessHotel/Sound/SoundClass/SCM_SFX_Fade.SCM_SFX_Fade"));

	SC_Master = LoadObject<USoundClass>(nullptr, TEXT("/Game/EndlessHotel/Sound/SoundClass/SC_Master.SC_Master"));
	SC_BGM = SC_Master->ChildClasses[Index_BGM];
	SC_SFX = SC_Master->ChildClasses[Index_SFX];
	SC_UI = SC_Master->ChildClasses[Index_UI];
	SC_Voice = SC_Master->ChildClasses[Index_Voice];
}

#pragma endregion

#pragma region SoundClass

float USoundController::GetSoundClassValue(const ESoundClassType& Type)
{
	switch (Type)
	{
	case ESoundClassType::Master:
		return SC_Master->Properties.Volume;

	case ESoundClassType::BGM:
		return SC_BGM->Properties.Volume;

	case ESoundClassType::SFX:
		return SC_SFX->Properties.Volume;

	case ESoundClassType::UI:
		return SC_UI->Properties.Volume;

	case ESoundClassType::Voice:
		return SC_Voice->Properties.Volume;
	}

	return 0.f;
}

void USoundController::SetSoundClassValue(const ESoundClassType& Type, float Value)
{
	switch (Type)
	{
	case ESoundClassType::Master:
		SC_Master->Properties.Volume = Value;
		break;

	case ESoundClassType::BGM:
		SC_BGM->Properties.Volume = Value;
		break;

	case ESoundClassType::SFX:
		SC_SFX->Properties.Volume = Value;
		break;

	case ESoundClassType::UI:
		SC_UI->Properties.Volume = Value;
		break;

	case ESoundClassType::Voice:
		SC_Voice->Properties.Volume = Value;
		break;
	}
}

#pragma endregion

#pragma region Fade In & Out

void USoundController::FadeSFXSound(bool bIsOpen)
{
	if (bIsOpen)
	{
		UGameplayStatics::PopSoundMixModifier(this, SCM_SFX_Mute);
		UGameplayStatics::PushSoundMixModifier(this, SCM_SFX_Fade);
	}
	else
	{
		UGameplayStatics::PushSoundMixModifier(this, SCM_SFX_Mute);
	}
}

#pragma endregion