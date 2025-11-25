// Copyright by 2025-2 WAP Game 2 team

#include "RoomSign/RoomSignActor.h"
#include "Components/StaticMeshComponent.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "GameSystem/SubSystem/AnomalyProgressSubSystem.h"

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

	DynamicMaterial = SignMesh->CreateAndSetMaterialInstanceDynamic(2);
	FLinearColor Offset = FLinearColor::Black;
	UAnomalyProgressSubSystem* Sub = GetGameInstance()->GetSubsystem<UAnomalyProgressSubSystem>();
	uint8 UVFloorValue = FMath::Clamp(Sub->Floor - 1, 1, 8);
	EFloorUV UVFloor = static_cast<EFloorUV>(UVFloorValue);
	float GValue = GetOffsetG(UVFloor);
	DynamicMaterial->GetVectorParameterValue(FName("OffsetUV"), Offset);
	Offset.G = GValue;
	DynamicMaterial->SetVectorParameterValue(FName("OffsetUV"), Offset);
}
