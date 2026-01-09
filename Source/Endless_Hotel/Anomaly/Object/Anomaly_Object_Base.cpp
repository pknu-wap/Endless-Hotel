// Copyright by 2025-2 WAP Game 2 team

#include "Anomaly/Object/Anomaly_Object_Base.h"
#include "Player/Character/EHPlayer.h"
#include "Player/Component/EHCameraComponent.h"
#include <Kismet/GameplayStatics.h>
#include "GameSystem/SubSystem/AnomalyProgressSubSystem.h"

#pragma region Player

void AAnomaly_Object_Base::KillPlayer()
{
	FTimerHandle DieTimerHandle;
	UAnomalyProgressSubSystem* Sub = GetGameInstance()->GetSubsystem<UAnomalyProgressSubSystem>();
	Sub->SetVerdictMode(EAnomalyVerdictMode::SolvedOnly);
	AEHPlayer* Player = Cast<AEHPlayer>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	UEHCameraComponent* PlayerCC = Player->FindComponentByClass<UEHCameraComponent>();

	// 아마도 애니메이션 넣으면 여기서 재생 처리

	PlayerCC->StartEyeEffect(false);

	GetWorld()->GetTimerManager().SetTimer(DieTimerHandle, FTimerDelegate::CreateWeakLambda(
		this,
		[Sub]()
		{
			Sub->ApplyVerdict();
		}), 10, false);
}

#pragma endregion