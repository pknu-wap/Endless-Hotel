// Copyright by 2025-2 WAP Game 2 team

#include "Component/Float/FloatComponent.h"
#include <Components/AudioComponent.h>

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

	FVector FloatVelocity = FVector(FMath::RandRange(-50.f, 50.f), FMath::RandRange(-50.f, 50.f), FMath::RandRange(100.f, 170.f));
	FVector RotationVelocity = FVector(FMath::RandRange(-30.f, 30.f), FMath::RandRange(-30.f, 30.f), FMath::RandRange(-30.f, 30.f));

	TargetMesh->SetPhysicsLinearVelocity(FloatVelocity);
	TargetMesh->SetPhysicsAngularVelocityInDegrees(RotationVelocity);

	FTimerHandle StopFloatTimer;
	GetWorld()->GetTimerManager().SetTimer(StopFloatTimer, this, &ThisClass::StopFloating, 3.0f, false);
}

void UFloatComponent::StopFloating()
{
	TargetMesh->SetPhysicsLinearVelocity(FVector::ZeroVector);
	TargetMesh->SetPhysicsAngularVelocityInDegrees(FVector::ZeroVector);

	FTimerHandle FreezeTimerHandle;
	GetWorld()->GetTimerManager().SetTimer(FreezeTimerHandle, this, &ThisClass::DropObject, 1.0f, false);
}

void UFloatComponent::DropObject()
{
	TargetMesh->SetEnableGravity(true);
	TargetMesh->SetNotifyRigidBodyCollision(true);
	TargetMesh->OnComponentHit.AddUniqueDynamic(this, &ThisClass::OnObjectDropped);

	Comp_Audio = NewObject<UAudioComponent>(this);
	Comp_Audio->SetSound(SW_Drop);
	Comp_Audio->AttachToComponent(TargetMesh.Get(), FAttachmentTransformRules::KeepRelativeTransform);

	for (auto* Target : Owner->GetComponentsByTag(UStaticMeshComponent::StaticClass(), TEXT("Float")))
	{
		auto* Mesh = Cast<UStaticMeshComponent>(Target);
		Mesh->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);
	}
}

void UFloatComponent::OnObjectDropped(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	Comp_Audio->Play();

	TargetMesh->SetNotifyRigidBodyCollision(false);
	TargetMesh->OnComponentHit.Clear();
}

#pragma endregion