// Copyright by 2025-2 WAP Game 2 team


#include "Anomaly/Object/MusicBox/Anomaly_Object_MusicBox.h"
#include "Anomaly/Base/Anomaly_Base.h"
#include <Components/AudioComponent.h>
#include <Kismet/KismetSystemLibrary.h>

#pragma region Base

AAnomaly_Object_MusicBox::AAnomaly_Object_MusicBox(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	Mesh_BoxBody = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BoxBody"));
	SetRootComponent(Mesh_BoxBody);
	Mesh_BoxRotator = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BoxRotator"));
	Mesh_BoxRotator->SetupAttachment(RootComponent);
	AC = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComponent"));
	AC->SetupAttachment(RootComponent);
	Object->SetupAttachment(RootComponent);
}

#pragma endregion

#pragma region PlayMusicBox

void AAnomaly_Object_MusicBox::PlayMusicBox()
{
	AC->Sound = Sound_MusicBox;
	AC->Play();
	bWaitingInteract = true;
	
	StartRotate();

	GetWorld()->GetTimerManager().ClearTimer(FailTimerHandle);
	GetWorld()->GetTimerManager().SetTimer(FailTimerHandle, FTimerDelegate::CreateWeakLambda(this, [this]()
		{
			bWaitingInteract = false;
			AC->Stop();
			bSolved = false;
			AAnomaly_Base::AnomalyDelegate.Broadcast(false);
		}), LimitTime, false);
}

void AAnomaly_Object_MusicBox::StartRotate()
{
	GetWorld()->GetTimerManager().SetTimer(
		RotateHandle,
		FTimerDelegate::CreateWeakLambda(this, [this]()
			{
				Mesh_BoxRotator->AddLocalRotation(TickRotation);
				if (!bWaitingInteract) GetWorld()->GetTimerManager().ClearTimer(RotateHandle);
			}),
		0.016f,
		true
	);
}

#pragma endregion

#pragma region Interact

void AAnomaly_Object_MusicBox::Interacted_Implementation()
{
	StartInteractaction();
}

void AAnomaly_Object_MusicBox::StopMusicBox()
{
	if (!bWaitingInteract) return;
	AC->Stop();
	bWaitingInteract = false;
	bSolved = true;

	GetWorld()->GetTimerManager().ClearTimer(FailTimerHandle);
}

void AAnomaly_Object_MusicBox::SetInteraction()
{
	switch (AnomalyID)
	{
	case 0:
		break;

	case 90:
		InteractAction = ([this]()
			{
				AAnomaly_Object_MusicBox::StopMusicBox();
			});
		break;
	}
}

#pragma endregion