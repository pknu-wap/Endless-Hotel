// Copyright by 2025-2 WAP Game 2 team

#include "Anomaly/Object/Anomaly_Object_Neapolitan.h"
#include "UI/World/Interact/UI_Interact.h"
#include "Component/LookAt/LookAtComponent.h"
#include <Components/WidgetComponent.h>

#define LOCTEXT_NAMESPACE "Anomaly_Object_Neapolitan"

#pragma region Base

AAnomaly_Object_Neapolitan::AAnomaly_Object_Neapolitan(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	Object = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Object"));
	Object->SetupAttachment(RootComponent);

	WC = CreateDefaultSubobject<UWidgetComponent>(TEXT("WC"));
	WC->SetupAttachment(Object);

	LAC = CreateDefaultSubobject<ULookAtComponent>(TEXT("LAC"));

	DescriptionText = LOCTEXT("Key1", "상호작용");
}

void AAnomaly_Object_Neapolitan::BeginPlay()
{
	Super::BeginPlay();
	bSolved = false;
	if (!WC) return;
	UI_Interact = Cast<UUI_Interact>(WC->GetUserWidgetObject());
	UI_Interact->SetDescription(DescriptionText);
	LAC->SettingWidgetComponent(WC);

	OriginalTransform = GetActorTransform();
}

#pragma endregion

#undef LOCTEXT_NAMESPACE

#pragma region Interact

void AAnomaly_Object_Neapolitan::Interacted_Implementation()
{
	bSolved = !bSolved;

	RestoreObjectTransform();
}

void AAnomaly_Object_Neapolitan::ShowInteractWidget_Implementation(bool bIsShow)
{
	UI_Interact->ShowDescription(bIsShow);
}

#pragma endregion

#pragma region Restore

void AAnomaly_Object_Neapolitan::RestoreObjectTransform()
{
	if (GetActorTransform().Equals(OriginalTransform))
	{
		return;
	}

	constexpr float RestoreDuration = 2.5f;
	constexpr float TimerInterval = 0.016f;

	GetWorld()->GetTimerManager().SetTimer(RestoreHandle, FTimerDelegate::CreateWeakLambda(this, [this]()
		{
			CurrentTime += GetWorld()->GetDeltaSeconds();

			float Alpha = FMath::Clamp(CurrentTime / RestoreDuration, 0.f, 1.f);

			FTransform CurrentTransform = GetActorTransform();

			FTransform TargetTransform;
			TargetTransform.Blend(CurrentTransform, OriginalTransform, Alpha);

			SetActorTransform(TargetTransform);

			if (Alpha >= 1)
			{
				SetActorTransform(OriginalTransform);
				GetWorld()->GetTimerManager().ClearTimer(RestoreHandle);
			}
		}), TimerInterval, true);
}

#pragma endregion