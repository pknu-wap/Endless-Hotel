// Copyright by 2026-1 WAP Game 2 team

#include "Actor/NoteBook/NoteBook.h"
#include "Component/Read/ReadComponent.h"
#include <Kismet/KismetSystemLibrary.h>

#pragma region Base

ANoteBook::ANoteBook(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	Comp_Read = CreateDefaultSubobject<UReadComponent>(TEXT("Comp_Read"));

	SM_Paper = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SM_Paper"));
	SM_Paper->SetupAttachment(RootComponent);
	SM_Paper->SetVisibility(false);
}

#pragma endregion

#pragma region Interact

void ANoteBook::Interact_Implementation(AEHCharacter* Interacter)
{
	Super::Interact_Implementation(Interacter);

	FInteractInfo Info = Component_Interact->GetSelectedInteractInfo();

	switch (Info.InteractType)
	{
	case EInteractType::Read:
		Comp_Read->MoveCameraToTarget(Interacter, this);
		break;
	}
}

#pragma endregion

#pragma region Page

void ANoteBook::TurnOverPage(bool bLeft)
{
	GetWorld()->GetTimerManager().ClearTimer(MoveHandle);
	ElapsedTime = 0.f;

	StartLocation = bLeft ? LeftPageLocation : RightPageLocation;
	EndLocation = bLeft ? RightPageLocation : LeftPageLocation;

	StartRotation = bLeft ? LeftPageRotation : RightPageRotation;
	EndRotation = bLeft ? RightPageRotation : LeftPageRotation;

	SM_Paper->SetRelativeLocationAndRotation(StartLocation, StartRotation);
	SM_Paper->SetVisibility(true);

	constexpr float Duration = 0.5f;

	GetWorld()->GetTimerManager().SetTimer(MoveHandle, FTimerDelegate::CreateWeakLambda(this, [this, Duration]()
		{
			ElapsedTime += GetWorld()->GetDeltaSeconds();
			float Alpha = FMath::Clamp(ElapsedTime / Duration, 0.f, 1.f);

			FVector TargetLoc = FMath::Lerp(StartLocation, EndLocation, Alpha);
			FQuat TargetQuat = FQuat::SlerpFullPath(StartRotation.Quaternion(), EndRotation.Quaternion(), Alpha);

			SM_Paper->SetRelativeLocationAndRotation(TargetLoc, TargetQuat);

			if (Alpha >= 1)
			{
				SM_Paper->SetVisibility(false);

				GetWorld()->GetTimerManager().ClearTimer(MoveHandle);
			}
		}), GetWorld()->GetDeltaSeconds(), true);
}

#pragma endregion