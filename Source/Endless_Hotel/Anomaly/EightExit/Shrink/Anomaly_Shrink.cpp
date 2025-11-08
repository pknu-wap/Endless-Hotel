// Copyright by 2025-2 WAP Game 2 team

#include "Anomaly/EightExit/Shrink/Anomaly_Shrink.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

#pragma region Activity

void AAnomaly_Shrink::ActivateAnomaly_Implementation(uint8 Anomaly_ID)
{
	Super::ActivateAnomaly_Implementation(Anomaly_ID);

	FTimerHandle StartHandle;
	GetWorld()->GetTimerManager().SetTimer(StartHandle, this, &ThisClass::ShrinkPlayer, 10, false);
}

#pragma endregion

#pragma region Shrink

void AAnomaly_Shrink::ShrinkPlayer()
{
	const float Multi_Scale = 0.3f;

	ACharacter* Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	USceneComponent* PlayerRC = Player->GetRootComponent();
	Player->GetCharacterMovement()->MaxWalkSpeed *= Multi_Scale;

	// 아직 플레이어 C++ 코드가 없어서 달리기와 해제 시 이동 속도가 복구 되는 것은 막지 못함
	// 추후 수정 예정

	FVector TargetScale = FVector(Multi_Scale, Multi_Scale, Multi_Scale);

	FTimerHandle ShrinkHandle;
	GetWorld()->GetTimerManager().SetTimer(ShrinkHandle, [this, PlayerRC, TargetScale, ShrinkHandle]() mutable
		{
			FVector CurrentScale = PlayerRC->GetRelativeScale3D();
			FVector ChangeScale = FMath::VInterpTo(CurrentScale, TargetScale, 0.01f, 1);
			PlayerRC->SetRelativeScale3D(ChangeScale);

			if (ChangeScale.Equals(TargetScale, 0.1f))
			{
				GetWorld()->GetTimerManager().ClearTimer(ShrinkHandle);
			}
		}, 0.01f, true);
}

#pragma endregion