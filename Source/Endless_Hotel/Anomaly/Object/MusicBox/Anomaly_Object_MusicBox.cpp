// Copyright by 2025-2 WAP Game 2 team


#include "Anomaly/Object/MusicBox/Anomaly_Object_MusicBox.h"
#include <Components/AudioComponent.h>

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
}

#pragma endregion

#pragma region PlayMusicBox

void AAnomaly_Object_MusicBox::PlayMusicBox()
{
	AC->Sound = Sound_MusicBox;
	AC->Play();
	bWaitingInteract = true;
	// 회전하는 등 연출 에셋 정한 이후에 추가하기
	GetWorld()->GetTimerManager().ClearTimer(FailTimerHandle);
	GetWorld()->GetTimerManager().SetTimer(FailTimerHandle, FTimerDelegate::CreateWeakLambda(this, [this]()
		{
			bWaitingInteract = false;
			AC->Stop();
			bSolved = false;
		}), LimitTime, false);
}

#pragma endregion

#pragma region Interact

void AAnomaly_Object_MusicBox::Interacted_Implementation()
{
	if (!bWaitingInteract) return;
	AC->Stop();
	bWaitingInteract = false;
	bSolved = true;
	GetWorld()->GetTimerManager().ClearTimer(FailTimerHandle);
}

#pragma endregion