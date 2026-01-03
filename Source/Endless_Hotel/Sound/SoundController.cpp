// Copyright by 2025-2 WAP Game 2 team

#include "Sound/SoundController.h"
#include <Sound/SoundClass.h>
#include <Components/TimelineComponent.h>

#pragma region Base

void USoundController::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

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

void USoundController::StartFadeSound(bool bIsOpen)
{
	CurrentSFXValue = SC_SFX->Properties.Volume;

	float TargetValue = bIsOpen ? OpenValue : CloseValue;
	FTimerHandle FadeHandle;
	GetWorld()->GetTimerManager().SetTimer(FadeHandle, FTimerDelegate::CreateWeakLambda(this, [this, TargetValue, bIsOpen, FadeHandle]() mutable
		{
			SetSoundClassValue(ESoundClassType::SFX, CurrentSFXValue * TargetValue);
			TargetValue = bIsOpen ? TargetValue + 0.02f : TargetValue - 0.02f;

			if (TargetValue <= OpenValue || TargetValue >= CloseValue)
			{
				GetWorld()->GetTimerManager().ClearTimer(FadeHandle);
			}
		}), 0.1f, true);
}

#pragma endregion