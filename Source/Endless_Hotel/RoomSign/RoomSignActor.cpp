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

	DynamicMaterial = SignMesh->CreateAndSetMaterialInstanceDynamic(0);
	UAnomalyProgressSubSystem* Sub = GetGameInstance()->GetSubsystem<UAnomalyProgressSubSystem>();
	uint8 SignIndex = Sub->Floor + 5;
	DynamicMaterial->SetScalarParameterValue(TEXT("SignIndex"), SignIndex);
}

#pragma endregion