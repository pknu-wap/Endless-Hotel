// Copyright by 2025-2 WAP Game 2 team

#include "Anomaly/Object/Neapolitan/MusicBox/Anomaly_Object_MusicBox.h"
#include "Anomaly/Event/Anomaly_Event.h"
#include "Player/Character/EHPlayer.h"
#include <Components/AudioComponent.h>
#include <Kismet/KismetSystemLibrary.h>
#include <Kismet/GameplayStatics.h>

#pragma region Base

AAnomaly_Object_MusicBox::AAnomaly_Object_MusicBox(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	Mesh_BoxRotator = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BoxRotator"));
	Mesh_BoxRotator->SetupAttachment(RootComponent);
	AC = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComponent"));
	AC->SetupAttachment(RootComponent);
}

#pragma endregion

#pragma region PlayMusicBox

void AAnomaly_Object_MusicBox::PlayMusicBox()
{
	bSolved = false;
	AC->Sound = Sound_MusicBox;
	AC->Play();
	
	StartRotate();

	GetWorld()->GetTimerManager().ClearTimer(FailTimerHandle);
	GetWorld()->GetTimerManager().SetTimer(FailTimerHandle,
		FTimerDelegate::CreateWeakLambda(this, [this]()
			{
				AC->Stop();
				bSolved = false;
				Component_Interact->ShowInteracting(false);
				Component_Interact->ActiveInteract(false);
			}), LimitTime, false);
}

void AAnomaly_Object_MusicBox::StartRotate()
{
	GetWorld()->GetTimerManager().SetTimer(RotateHandle,
		FTimerDelegate::CreateWeakLambda(this, [this]()
			{
				Mesh_BoxRotator->AddLocalRotation(TickRotation);
				if (!GetWorld()->GetTimerManager().IsTimerActive(FailTimerHandle))
				{
					GetWorld()->GetTimerManager().ClearTimer(RotateHandle);
				}
			}), 0.016f, true);
}

#pragma endregion

#pragma region Interact

void AAnomaly_Object_MusicBox::Interact(AEHCharacter* Interacter)
{
	Super::Interact(Interacter);

	FInteractInfo Info = Component_Interact->GetSelectedInteractInfo();

	switch (Info.InteractType)
	{
	case EInteractType::TurnOff:
		StopMusicBox();
		break;
	}
}

void AAnomaly_Object_MusicBox::StopMusicBox()
{
	AC->Stop();
	GetWorld()->GetTimerManager().ClearTimer(FailTimerHandle);
}

#pragma endregion