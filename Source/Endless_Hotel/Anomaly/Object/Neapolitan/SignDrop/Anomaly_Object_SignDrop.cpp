// Copyright by 2025-2 WAP Game 2 team

#include "Anomaly/Object/Neapolitan/SignDrop/Anomaly_Object_SignDrop.h"
#include "Actor/RoomSign/RoomSignActor.h"
#include <GameFramework/PlayerController.h>
#include <Kismet/GameplayStatics.h>

#pragma region Reset

void AAnomaly_Object_SignDrop::Reset()
{
	OriginalTransform.SetLocation(FVector::ZeroVector);

	if (TargetSign.IsValid())
	{
		TargetSign->GetRootComponent()->SetVisibility(true, true);
	}

	Super::Reset();
}

#pragma endregion

#pragma region Drop

void AAnomaly_Object_SignDrop::ExecuteSignDrop()
{
	int32 RandomIndex = FMath::RandRange(0, RoomSigns.Num() - 1);
	TargetSign = RoomSigns[RandomIndex].Get();
	auto* RootComp = TargetSign->GetRootComponent();
	RootComp->SetVisibility(false, true);

	auto* PC = GetWorld()->GetFirstPlayerController();
	PC->ClientStartCameraShake(CameraShakeClass, 0.3f);

	OriginalTransform = RootComp->GetComponentTransform();

	FVector TargetVec = RootComp->GetComponentLocation();
	TargetVec += RootComp->GetRightVector() * 10;
	FRotator TargetRot = RootComp->GetComponentRotation();

	SetActorLocationAndRotation(TargetVec, TargetRot, false, nullptr, ETeleportType::TeleportPhysics);

	DropSign();
}

void AAnomaly_Object_SignDrop::DropSign()
{
	Object->SetEnableGravity(true);
	Object->SetSimulatePhysics(true);

	UGameplayStatics::PlaySoundAtLocation(this, DropSound, GetActorLocation());
}

#pragma endregion

#pragma region Interact

void AAnomaly_Object_SignDrop::Interact(AEHCharacter* Interacter)
{
	Super::Interact(Interacter);

	auto Info = Component_Interact->GetSelectedInteractInfo();

	switch (Info.InteractType)
	{
	case EInteractType::Restore:
		StartRestoring();
		break;
	}
}

#pragma endregion