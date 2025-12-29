// Copyright by 2025-2 WAP Game 2 team

#include "Component/LookAt/LookAtComponent.h"
#include "Components/WidgetComponent.h"

#pragma region Base

ULookAtComponent::ULookAtComponent(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	PrimaryComponentTick.bCanEverTick = true;
}

void ULookAtComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	LookAtPlayer();
}

#pragma endregion

#pragma region LookAt

void ULookAtComponent::LookAtPlayer()
{
	if (!WC)
	{
		return;
	}

	APlayerCameraManager* CamMan = GetWorld()->GetFirstPlayerController()->PlayerCameraManager;
	FVector TargetVec = CamMan->GetCameraLocation() - WC->GetComponentLocation();
	FRotator TargetRot = TargetVec.Rotation();
	TargetRot.Roll = 0;

	WC->SetWorldRotation(TargetRot);
}

#pragma endregion