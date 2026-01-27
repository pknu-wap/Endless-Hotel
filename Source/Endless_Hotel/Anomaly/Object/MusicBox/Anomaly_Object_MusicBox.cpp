// Copyright by 2025-2 WAP Game 2 team


#include "Anomaly/Object/MusicBox/Anomaly_Object_MusicBox.h"
#include "Anomaly/Base/Anomaly_Base.h"
#include "Player/Character/EHPlayer.h"
#include "Component/AnomalyInteract/AnomalyInteractComponent.h"
#include "Component/AnomalyInteract/MusicBox/StopMusicBox_Interact.h"
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

	MusicRotate = CreateDefaultSubobject<UStopMusicBox_Interact>(TEXT("MusciRotate"));
}

void AAnomaly_Object_MusicBox::BeginPlay()
{
	Super::BeginPlay();
	CurrentInteractionUpdate();
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
			AEHPlayer* Player = Cast<AEHPlayer>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
			if (!Player) return;
			Player->DieDelegate.Broadcast(EDeathReason::Music);
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

#pragma region InteractActions

void AAnomaly_Object_MusicBox::StopMusicBox()
{
	if (!bWaitingInteract) return;
	AC->Stop();
	bWaitingInteract = false;
	bSolved = true;

	GetWorld()->GetTimerManager().ClearTimer(FailTimerHandle);
}

#pragma endregion