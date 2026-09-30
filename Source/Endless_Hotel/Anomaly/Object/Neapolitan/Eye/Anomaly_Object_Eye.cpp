// Copyright by 2026-1 WAP Game 2 team

#include "Anomaly/Object/Neapolitan/Eye/Anomaly_Object_Eye.h"
#include "Player/Controller/EHPlayerController.h"
#include "Player/Character/EHPlayer.h"
#include <Kismet/GameplayStatics.h>
#include <Kismet/KismetMathLibrary.h>

#include "Player/Camera/EHPlayerCameraManager.h"

#pragma region Base

void AAnomaly_Object_Eye::InitializeOnAnomalySpawned()
{
	Super::InitializeOnAnomalySpawned();
	Object->SetVisibility(false);
}

#pragma endregion

#pragma region EyeFocus

void AAnomaly_Object_Eye::StartEyeFocus()
{
	Object->SetVisibility(true);
	const auto& CachedPlayer = Cast<AEHPlayer>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	CachedPlayer->OnDie.AddUObject(this, &ThisClass::StopEyeFocus);
	GetWorld()->GetTimerManager().SetTimer(FocusHandle, FTimerDelegate::CreateWeakLambda(this, [this, CachedPlayer]()
	{
		const FRotator NewRotation = UKismetMathLibrary::FindLookAtRotation(this->GetActorLocation(), CachedPlayer->GetActorLocation()) + CorrectionRotation;
		this->SetActorRotation(NewRotation);
	}), 0.016f, true);
}

void AAnomaly_Object_Eye::StopEyeFocus(const EDeathReason& DeathReason)
{
	GetWorldTimerManager().ClearTimer(FocusHandle);
}

#pragma endregion
