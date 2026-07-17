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
		SetupAnomalyAction(&AAnomaly_Object_FireExtinguisher::Explode);
		ActiveTrigger();
		break;
	}
}

void AAnomaly_FireExtinguisher::DisableAnomaly()
{
	Super::DisableAnomaly();

	ShowBlurWiget(false);
}

void AAnomaly_FireExtinguisher::StartAnomalyAction()
{
	Super::StartAnomalyAction();

	ShowBlurWiget(true);
	PlayDownAnimMontage();
}

#pragma endregion

#pragma region Blur

void AAnomaly_FireExtinguisher::ShowBlurWiget(bool bIsStart)
{
	UUI_Controller* UICon = GetGameInstance()->GetSubsystem<UUI_Controller>();
	UUI_Base* BlurWidget = UICon->GetHUDWidget();
	Cast<UUI_HUD_InGame>(BlurWidget)->AnomalyBlur(bIsStart);

	if (!bIsStart)
	{
		AC->Stop();
		GetWorld()->GetTimerManager().ClearTimer(FadeOutHandle);
		return;
	}
	
	AC = UGameplayStatics::CreateSound2D(GetWorld(), SW_Blur);
	AC->Play();

	GetWorld()->GetTimerManager().SetTimer(FadeOutHandle, FTimerDelegate::CreateWeakLambda(this, [this]()
		{
			AC->FadeOut(1, 0);
		}), 9, false);
}

#pragma endregion

#pragma region Down

void AAnomaly_FireExtinguisher::PlayDownAnimMontage()
{
	auto* Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
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