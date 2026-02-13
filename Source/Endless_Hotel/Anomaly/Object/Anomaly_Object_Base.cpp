// Copyright by 2025-2 WAP Game 2 team

#include "Anomaly/Object/Anomaly_Object_Base.h"
#include <Components/WidgetComponent.h>

#pragma region Base

AAnomaly_Object_Base::AAnomaly_Object_Base(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	Object = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Object"));
	SetRootComponent(Object);

	Component_Widget = CreateDefaultSubobject<UWidgetComponent>(TEXT("Component Widget"));
	Component_Widget->SetupAttachment(RootComponent);
	Component_Widget->SetWidgetSpace(EWidgetSpace::Screen);

	Component_Interact = CreateDefaultSubobject<UInteractComponent>(TEXT("Component_Interact"));
}

void AAnomaly_Object_Base::BeginPlay()
{
	Super::BeginPlay();

	if (!Component_Interact->CanInteract())
	{
		Component_Widget->SetActive(false);
	}

	/*SetInteraction();*/
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