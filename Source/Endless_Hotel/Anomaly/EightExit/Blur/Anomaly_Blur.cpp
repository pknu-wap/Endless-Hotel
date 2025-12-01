// Copyright by 2025-2 WAP Game 2 team

#include "Anomaly/EightExit/Blur/Anomaly_Blur.h"
#include "UI/Controller/UI_Controller.h"
#include "Components/AudioComponent.h"

#pragma region Base

AAnomaly_Blur::AAnomaly_Blur(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	AC = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComponent"));
	AC->SetupAttachment(RootComponent);
}

#pragma endregion

#pragma region Activity

void AAnomaly_Blur::ActivateAnomaly(uint8 Anomaly_ID)
{
	Super::ActivateAnomaly(Anomaly_ID);

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
	UICon->OpenWidget(UI_Blur, EWidgetType::PopUp, EInputModeType::GameOnly);

	AC->Sound = Sound_Blur;
	AC->Play();

	FTimerHandle FadeOutHandle;
	GetWorld()->GetTimerManager().SetTimer(FadeOutHandle, FTimerDelegate::CreateWeakLambda(this, [this]()
		{
			AC->FadeOut(1, 0);
		}), 9, false);
}

#pragma endregion