// Copyright by 2026-1 WAP Game 2 team

#include "Anomaly/Object/Neapolitan/Radio/Anomaly_Object_Radio.h"
#include "UI/Controller/UI_Controller.h"
#include <Components/StaticMeshComponent.h>
#include <Components/TimelineComponent.h>
#include <Components/AudioComponent.h>
#include <Sound/SoundWave.h>

#pragma region Base

AAnomaly_Object_Radio::AAnomaly_Object_Radio(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	SM_Radio_Pointer = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SM_Radio_Pointer"));
	SM_Radio_Pointer->SetupAttachment(Object);

	Timeline_PointerSpin = CreateDefaultSubobject<UTimelineComponent>(TEXT("Timeline_PointerSpin"));

	AC = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComponent"));
	AC->SetupAttachment(RootComponent);
}

void AAnomaly_Object_Radio::BeginPlay()
{
	Super::BeginPlay();

	OriginalPointerRotation = SM_Radio_Pointer->GetRelativeRotation();

	FOnTimelineFloat Update_PointerSpin;
	Update_PointerSpin.BindUFunction(this, "UpdatePointerSpin");
	Timeline_PointerSpin->AddInterpFloat(CV_PointerSpin, Update_PointerSpin);

	Timeline_PointerSpin->SetTimelineLengthMode(ETimelineLengthMode::TL_LastKeyFrame);
	Timeline_PointerSpin->SetLooping(true);

	AC->OnAudioFinished.AddUniqueDynamic(this, &ThisClass::FinishMove);
}

#pragma region Radio

void AAnomaly_Object_Radio::PointerMoving()
{
	int32 RandomIndex = FMath::RandRange(0, Sound_Radio.Num() - 1);
	AC->SetSound(Sound_Radio[RandomIndex]);
	AC->Play();

	if (RadioSubtitles.IsValidIndex(RandomIndex))
	{
		auto* UICon = GetGameInstance()->GetSubsystem<UUI_Controller>();

		if (IsValid(UICon))
		{
			for (const FRadioSubtitleLine& Line : RadioSubtitles[RandomIndex].Lines)
			{
				if (Line.Text.IsEmpty()	|| Line.StartTime <= 0.f || Line.Duration <= 0.f)
				{
					continue;
				}

				UICon->ShowSubTitle(Line.Text, Line.StartTime, Line.Duration);
			}
		}
	}

	Timeline_PointerSpin->SetPlayRate(1.f);
	Timeline_PointerSpin->PlayFromStart();
}

#pragma endregion

#pragma region RotateMove

void AAnomaly_Object_Radio::FinishMove()
{
	Timeline_PointerSpin->Stop();
}

#pragma endregion

#pragma region PointerTimeline

void AAnomaly_Object_Radio::UpdatePointerSpin(float Value)
{
	FRotator Target = OriginalPointerRotation;
	Target.Roll = OriginalPointerRotation.Roll + Value;
	SM_Radio_Pointer->SetRelativeRotation(Target);
}
#pragma endregion

#pragma region Interact

void AAnomaly_Object_Radio::Interact(AEHCharacter* Interacter)
{
	Super::Interact(Interacter);

	FInteractInfo Info = Component_Interact->GetSelectedInteractInfo();

	switch (Info.InteractType)
	{
	case EInteractType::TurnOff:
		StopRadio();
		break;
	}
}

void AAnomaly_Object_Radio::StopRadio()
{
	AC->FadeOut(0.5f, 0.f);

	Timeline_PointerSpin->SetPlayRate(0.2f);

	FTimerHandle TempHandle;
	GetWorld()->GetTimerManager().SetTimer(TempHandle, FTimerDelegate::CreateWeakLambda(this, [this]()
	{
		Timeline_PointerSpin->Stop();
	}), 0.5f, false);
}

#pragma endregion