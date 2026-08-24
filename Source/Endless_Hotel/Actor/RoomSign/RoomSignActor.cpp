// Copyright by 2025-2 WAP Game 2 team

#include "Actor/RoomSign/RoomSignActor.h"
#include "GameSystem/SubSystem/FloorProgressSubsystem.h"
#include <Materials/MaterialInstanceDynamic.h>

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

	auto* Sub = GetGameInstance()->GetSubsystem<UFloorProgressSubsystem>();
	Sub->FloorChange_Reset.AddUniqueDynamic(this, &ThisClass::Reset);
}

#pragma endregion

#pragma region Reset

void ARoomSignActor::Reset()
{
	DynamicMaterial = SignMesh->CreateAndSetMaterialInstanceDynamic(2);
	FLinearColor Offset = FLinearColor::Black;
	auto* Sub = GetGameInstance()->GetSubsystem<UFloorProgressSubsystem>();
	uint8 UVFloorValue = FMath::Clamp(Sub->Floor, 1, 8);
	EFloorUV UVFloor = static_cast<EFloorUV>(UVFloorValue);
	float GValue = GetOffsetG(UVFloor);
	DynamicMaterial->GetVectorParameterValue(FName("OffsetUV"), Offset);
	Offset.G = GValue;
	DynamicMaterial->SetVectorParameterValue(FName("OffsetUV"), Offset);
}

#pragma endregion