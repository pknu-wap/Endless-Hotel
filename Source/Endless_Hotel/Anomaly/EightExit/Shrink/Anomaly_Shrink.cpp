// Copyright by 2025-2 WAP Game 2 team

#include "Anomaly/EightExit/Shrink/Anomaly_Shrink.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Player/Controller/EHPlayerController.h"

#pragma region Activity

void AAnomaly_Shrink::ActivateAnomaly_Implementation(uint8 Anomaly_ID)
{
	Super::ActivateAnomaly_Implementation(Anomaly_ID);

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

	FVector TargetScale = FVector(Multi_Scale, Multi_Scale, Multi_Scale);

	FTimerHandle ShrinkHandle;
	GetWorld()->GetTimerManager().SetTimer(ShrinkHandle, FTimerDelegate::CreateWeakLambda(this, [this, PlayerRC, TargetScale, ShrinkHandle]() mutable
		{
			FVector CurrentScale = PlayerRC->GetRelativeScale3D();
			FVector ChangeScale = FMath::VInterpTo(CurrentScale, TargetScale, 0.01f, 1);
			PlayerRC->SetRelativeScale3D(ChangeScale);

			if (ChangeScale.Equals(TargetScale, 0.1f))
			{
				GetWorld()->GetTimerManager().ClearTimer(ShrinkHandle);
			}
		}), 0.01f, true);
}

#pragma endregion