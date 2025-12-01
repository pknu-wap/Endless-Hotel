// Copyright by 2025-2 WAP Game 2 team

#include "Anomaly/EightExit/Shrink/Anomaly_Shrink.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Player/Controller/EHPlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/CapsuleComponent.h"

#pragma region Activity

void AAnomaly_Shrink::ActivateAnomaly(uint8 Anomaly_ID)
{
	Super::ActivateAnomaly(Anomaly_ID);

	FTimerHandle StartHandle;
	GetWorld()->GetTimerManager().SetTimer(StartHandle, FTimerDelegate::CreateWeakLambda(this, [this]()
		{
			ShrinkPlayer();
		}), 20, false);
}

#pragma endregion

#pragma region Shrink

void AAnomaly_Shrink::ShrinkPlayer()
{
	const float Multi_Scale = 0.3f;

	ACharacter* Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	USceneComponent* PlayerRC = Player->GetRootComponent();
	Player->GetCharacterMovement()->MaxWalkSpeed *= Multi_Scale;

	auto* PC = Cast<AEHPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	PC->bCanRun = false;
	PC->bCanCrouch = false;

	FVector TargetScale = FVector(Multi_Scale, Multi_Scale, Multi_Scale);

	USpringArmComponent* SpringArm = Player->FindComponentByClass<USpringArmComponent>();
	FVector SpringArmStartLoc = SpringArm->GetRelativeLocation();
	FVector SpringArmTargetLoc = FVector(22.f, 10.f, 0.f);

	UCapsuleComponent* Capsule = Player->GetCapsuleComponent();
	float OriginalRadius = Capsule->GetUnscaledCapsuleRadius();
	float OriginalHalf = Capsule->GetUnscaledCapsuleHalfHeight();

	float TargetRadius = OriginalRadius * 2.f;
	float TargetHalf = OriginalHalf * 1.0;

	FTimerHandle ShrinkHandle;
	GetWorld()->GetTimerManager().SetTimer(ShrinkHandle, FTimerDelegate::CreateWeakLambda(this, [this, PlayerRC, TargetScale, SpringArm, SpringArmStartLoc, SpringArmTargetLoc, Capsule, TargetRadius, TargetHalf, ShrinkHandle]() mutable
		{
			FVector CurrentScale = PlayerRC->GetRelativeScale3D();
			FVector ChangeScale = FMath::VInterpTo(CurrentScale, TargetScale, 0.01f, 1);
			PlayerRC->SetRelativeScale3D(ChangeScale);

			FVector CurrentLoc = SpringArm->GetRelativeLocation();
			FVector NewLoc = FMath::VInterpTo(CurrentLoc, SpringArmTargetLoc, 0.01f, 1.0f);
			SpringArm->SetRelativeLocation(NewLoc);

			float NewRad = FMath::FInterpTo(Capsule->GetUnscaledCapsuleRadius(), TargetRadius, 0.01f, 1.0f);
			float NewHalf = FMath::FInterpTo(Capsule->GetUnscaledCapsuleHalfHeight(), TargetHalf, 0.01f, 1.0f);
			Capsule->SetCapsuleSize(NewRad, NewHalf);

			if (ChangeScale.Equals(TargetScale, 0.1f))
			{
				GetWorld()->GetTimerManager().ClearTimer(ShrinkHandle);
			}
		}), 0.01f, true);
}

#pragma endregion

