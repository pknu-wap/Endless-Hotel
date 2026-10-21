// Copyright by 2025-2 WAP Game 2 team

#include "Anomaly/Object/Neapolitan/SignDrop/Anomaly_Object_SignDrop.h"
#include "GameSystem/SubSystem/FloorProgressSubsystem.h"
#include <GameFramework/PlayerController.h>
#include <Kismet/GameplayStatics.h>
#include <Materials/MaterialInstanceDynamic.h>

#pragma region Base

void AAnomaly_Object_SignDrop::BeginPlay()
{
	Super::BeginPlay();
	DynamicMaterial = Object->CreateAndSetMaterialInstanceDynamic(2);
}

#pragma endregion

#pragma region Init

void AAnomaly_Object_SignDrop::InitializeOnAnomalySpawned()
{
	Super::InitializeOnAnomalySpawned();

	FLinearColor Offset = FLinearColor::Black;
	auto* FloorSub = GetGameInstance()->GetSubsystem<UFloorProgressSubsystem>();
	uint8 UVFloorValue = FMath::Clamp(FloorSub->GetFloor(), 1, 8);
	EFloorUV UVFloor = static_cast<EFloorUV>(UVFloorValue);
	float GValue = GetOffsetG(UVFloor);
	DynamicMaterial->GetVectorParameterValue(FName("OffsetUV"), Offset);
	Offset.G = GValue;
	DynamicMaterial->SetVectorParameterValue(FName("OffsetUV"), Offset);
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
		OriginalTransform = Object->GetRelativeTransform();
		StartRestoring();
		break;
	}
}

#pragma endregion

#pragma region Drop

void AAnomaly_Object_SignDrop::ExecuteSignDrop()
{
	auto* PC = GetWorld()->GetFirstPlayerController();
	PC->ClientStartCameraShake(CameraShakeClass, 0.3f);

	Object->SetEnableGravity(true);
	Object->SetSimulatePhysics(true);

	UGameplayStatics::PlaySoundAtLocation(this, DropSound, GetActorLocation());
}

#pragma endregion