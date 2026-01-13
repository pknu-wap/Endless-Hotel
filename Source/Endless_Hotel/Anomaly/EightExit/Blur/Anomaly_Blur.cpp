// Copyright by 2025-2 WAP Game 2 team

#include "Anomaly/EightExit/Blur/Anomaly_Blur.h"
#include "UI/Controller/UI_Controller.h"
#include "UI/PopUp/Blur/UI_PopUp_Blur.h"
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

void AAnomaly_Blur::ActivateAnomaly()
{
	Super::ActivateAnomaly();

	FTimerHandle StartHandle;
	GetWorld()->GetTimerManager().SetTimer(StartHandle, FTimerDelegate::CreateWeakLambda(this, [this]()
		{
			ShowBlurWiget();
		}), 15, false);
}

#pragma endregion

#pragma region Blur

void AAnomaly_Blur::ShowBlurWiget()
{
	UUI_Controller* UICon = GetGameInstance()->GetSubsystem<UUI_Controller>();
	UUI_Base* BlurWidget = UICon->OpenWidget(UI_Blur);
	Cast<UUI_PopUp_Blur>(BlurWidget)->AnomalyBlur();

	AC->Sound = Sound_Blur;
	AC->Play();

	FTimerHandle FadeOutHandle;
	GetWorld()->GetTimerManager().SetTimer(FadeOutHandle, FTimerDelegate::CreateWeakLambda(this, [this]()
		{
			AC->FadeOut(1, 0);
		}), 9, false);
}

#pragma endregion