// Copyright by 2025-2 WAP Game 2 team

#include "Anomaly/EightExit/Blur/Anomaly_Blur.h"
#include "UI/Controller/UI_Controller.h"
#include "UI/HUD/InGame/UI_HUD_InGame.h"
#include <Components/AudioComponent.h>

#pragma region Base

AAnomaly_Blur::AAnomaly_Blur(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	AC = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComponent"));
	AC->SetupAttachment(RootComponent);
}

#pragma endregion

#pragma region Activity

void AAnomaly_Blur::SetAnomalyState()
{
	Super::SetAnomalyState();

	switch (AnomalyName)
	{
	case EAnomalyName::Blur:
		ActiveTrigger();
		break;
	}
}

void AAnomaly_Blur::StartAnomalyAction()
{
	ShowBlurWiget();
}

#pragma endregion

#pragma region Blur

void AAnomaly_Blur::ShowBlurWiget()
{
	UUI_Controller* UICon = GetGameInstance()->GetSubsystem<UUI_Controller>();
	UUI_Base* BlurWidget = UICon->GetCurrentHUDWidget();
	Cast<UUI_HUD_InGame>(BlurWidget)->AnomalyBlur();

	AC->Sound = Sound_Blur;
	AC->Play();

	FTimerHandle FadeOutHandle;
	GetWorld()->GetTimerManager().SetTimer(FadeOutHandle, FTimerDelegate::CreateWeakLambda(this, [this]()
		{
			AC->FadeOut(1, 0);
		}), 9, false);
}

#pragma endregion