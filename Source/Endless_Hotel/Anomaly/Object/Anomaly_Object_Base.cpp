// Copyright by 2025-2 WAP Game 2 team

#include "Anomaly/Object/Anomaly_Object_Base.h"
#include "Player/Character/EHPlayer.h"
#include "Player/Component/EHCameraComponent.h"
#include "UI/World/Interact/UI_Interact.h"
#include "Component/LookAt/LookAtComponent.h"
#include "GameSystem/SubSystem/AnomalyProgressSubSystem.h"
#include "Component/AnomalyInteract/AnomalyInteractComponent.h"
#include <Kismet/GameplayStatics.h>
#include <Components/WidgetComponent.h>


#pragma region Base

AAnomaly_Object_Base::AAnomaly_Object_Base(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	Object = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Object"));
	SetRootComponent(Object);

	WC = CreateDefaultSubobject<UWidgetComponent>(TEXT("WC"));
	WC->SetupAttachment(RootComponent);

	LAC = CreateDefaultSubobject<ULookAtComponent>(TEXT("LAC"));
}

void AAnomaly_Object_Base::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	InteractComponents.Empty();
	GetComponents<UAnomalyInteractComponent>(InteractComponents);
}

#pragma endregion

#pragma region Interact

void AAnomaly_Object_Base::Interacted_Implementation()
{
	InteractComponents[CurrentInteractIndex]->Interacted_Implementation();
}

void AAnomaly_Object_Base::ShowInteractWidget_Implementation(bool bIsShow)
{
	if (!UI_Interact) return;
	UI_Interact->ShowDescription(bIsShow);
}

void AAnomaly_Object_Base::CurrentInteractionUpdate(uint8 InteractionNumber)
{
	CurrentInteractIndex = InteractionNumber;
	InteractComponents[CurrentInteractIndex]->SetAnomalyInteract();
}

#pragma endregion

#pragma region Restore

void AAnomaly_Object_Base::RestoreObjectTransform()
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