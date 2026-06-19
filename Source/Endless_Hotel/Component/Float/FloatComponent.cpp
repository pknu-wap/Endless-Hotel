// Copyright by 2025-2 WAP Game 2 team

#include "Component/Float/FloatComponent.h"

#pragma region Base

void UFloatComponent::BeginPlay()
{
	Super::BeginPlay();

	TargetMesh = Cast<UPrimitiveComponent>(Owner->GetRootComponent());
}

#pragma endregion

#pragma region Float

void UFloatComponent::StartFloating()
{
	TargetMesh->SetSimulatePhysics(true);
	TargetMesh->SetEnableGravity(false);
	TargetMesh->SetPhysicsLinearVelocity(FVector::ZeroVector);

	FVector FloatVelocity = FVector(FMath::RandRange(-30.f, 30.f), FMath::RandRange(-30.f, 30.f), FMath::RandRange(50.f, 150.f));
	FVector RotationVelocity = FVector(FMath::RandRange(-30.f, 30.f), FMath::RandRange(-30.f, 30.f), FMath::RandRange(-30.f, 30.f));

	TargetMesh->SetPhysicsLinearVelocity(FloatVelocity);
	TargetMesh->SetPhysicsAngularVelocityInDegrees(RotationVelocity);

	FTimerHandle StopFloatTimer;
	GetWorld()->GetTimerManager().SetTimer(StopFloatTimer, this, &ThisClass::StopFloating, 6.0f, false);
}

void UFloatComponent::StopFloating()
{
	TargetMesh->SetPhysicsLinearVelocity(FVector::ZeroVector);
	TargetMesh->SetPhysicsAngularVelocityInDegrees(FVector::ZeroVector);

	FTimerHandle FreezeTimerHandle;
	GetWorld()->GetTimerManager().SetTimer(FreezeTimerHandle, this, &ThisClass::DropObject, 1.5f, false);
}

void UFloatComponent::DropObject()
{
	TargetMesh->SetEnableGravity(true);
}

#pragma endregion