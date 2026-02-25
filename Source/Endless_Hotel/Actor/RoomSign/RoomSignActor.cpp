// Copyright by 2025-2 WAP Game 2 team

#include "Actor/RoomSign/RoomSignActor.h"
#include "GameSystem/SubSystem/GameSystem.h"
#include <Components/StaticMeshComponent.h>
#include <Materials/MaterialInstanceDynamic.h>
#include <Components/AudioComponent.h>
#include <Kismet/GameplayStatics.h>

#pragma region Base

ARoomSignActor::ARoomSignActor(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	SignMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SignMesh"));
	SetRootComponent(SignMesh);
}

void ARoomSignActor::BeginPlay()
{
	Super::BeginPlay();

	SaveOriginalTransform();
	DynamicMaterial = SignMesh->CreateAndSetMaterialInstanceDynamic(2);
	FLinearColor Offset = FLinearColor::Black;
	UGameSystem* Sub = GetGameInstance()->GetSubsystem<UGameSystem>();
	uint8 UVFloorValue = FMath::Clamp(Sub->Floor - 1, 1, 8);
	EFloorUV UVFloor = static_cast<EFloorUV>(UVFloorValue);
	float GValue = GetOffsetG(UVFloor);
	DynamicMaterial->GetVectorParameterValue(FName("OffsetUV"), Offset);
	Offset.G = GValue;
	DynamicMaterial->SetVectorParameterValue(FName("OffsetUV"), Offset);
}

#pragma endregion

#pragma region Drop

void ARoomSignActor::DropSign()
{
	if (bDropped || !SignMesh) return;

	bDropped = true;

	SignMesh->SetSimulatePhysics(true);
	SignMesh->SetEnableGravity(true);

	if (DropSound)
	{
		UGameplayStatics::PlaySoundAtLocation(
			this,
			DropSound,
			GetActorLocation()
		);
	}

	FTimerHandle PhysicTimer;
	GetWorld()->GetTimerManager().SetTimer(
		PhysicTimer,
		FTimerDelegate::CreateWeakLambda(this, [this]()
			{
				SignMesh->SetSimulatePhysics(false);
			}),
		1.0f,
		false
	);
}

void ARoomSignActor::SaveOriginalTransform()
{
	OriginalTransform = GetActorTransform();
}

#pragma endregion
