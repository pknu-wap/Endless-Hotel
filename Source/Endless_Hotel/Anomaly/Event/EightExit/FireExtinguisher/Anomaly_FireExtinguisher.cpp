// Copyright by 2025-2 WAP Game 2 team

#include "Anomaly/Event/EightExit/FireExtinguisher/Anomaly_FireExtinguisher.h"
#include "Anomaly/Object/EightExit/FireExtinguisher/Anomaly_Object_FireExtinguisher.h"
#include "UI/Controller/UI_Controller.h"
#include "UI/HUD/InGame/UI_HUD_InGame.h"
#include "Player/Character/EHPlayer.h"
#include "Player/Controller/EHPlayerController.h"
#include <Kismet/GameplayStatics.h>
#include <Components/AudioComponent.h>

#pragma region Activity

void AAnomaly_FireExtinguisher::SetAnomalyState()
{
	Super::SetAnomalyState();

	switch (AnomalyID)
	{
	case EAnomalyID::FireExt_Explode:
		SetupAnomalyAction<AAnomaly_Object_FireExtinguisher>(&AAnomaly_Object_FireExtinguisher::Explode);
		SetupAnomalyAction<ThisClass>(&ThisClass::ShowBlurWiget, FAnomalyActionInfo(), true);
		SetupAnomalyAction<ThisClass>(&ThisClass::PlayDownAnimMontage);
		ActiveTrigger();
		break;
	}
}

void AAnomaly_FireExtinguisher::DisableAnomaly()
{
	Super::DisableAnomaly();

	ShowBlurWiget(false);
}

#pragma endregion

#pragma region Blur

void AAnomaly_FireExtinguisher::ShowBlurWiget(bool bIsStart)
{
	if (!bIsStart)
	{
		AC->Stop();
		GetWorld()->GetTimerManager().ClearTimer(FadeOutHandle);
		return;
	}

	auto* UICon = GetGameInstance()->GetSubsystem<UUI_Controller>();
	auto* BlurWidget = Cast<UUI_HUD_InGame>(UICon->GetHUDWidget());
	BlurWidget->EyeEffectBlur(true);
	
	AC = UGameplayStatics::CreateSound2D(GetWorld(), SW_Blur);
	AC->Play();

	GetWorld()->GetTimerManager().SetTimer(FadeOutHandle, FTimerDelegate::CreateWeakLambda(this, [this, BlurWidget]()
		{
			AC->FadeOut(1, 0);
			BlurWidget->EyeEffectBlur(false);
		}), 7, false);
}

#pragma endregion

#pragma region Down

void AAnomaly_FireExtinguisher::PlayDownAnimMontage()
{
	auto* Player = Cast<AEHPlayer>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	Player->PlayAnimMontage(AM_DownUp);
	
	auto* PC = Cast<AEHPlayerController>(Player->GetController());
	PC->SetPlayerInputAble(false);

	const float DownDuration = AM_DownUp->GetPlayLength();
	FTimerHandle UpHandle;
	GetWorld()->GetTimerManager().SetTimer(UpHandle, FTimerDelegate::CreateWeakLambda(this, [this, PC]()
		{
			PC->SetPlayerInputAble(true);
		}), DownDuration, false);
}

#pragma endregion