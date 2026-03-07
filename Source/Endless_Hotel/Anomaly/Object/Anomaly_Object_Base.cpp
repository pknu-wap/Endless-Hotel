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

    bSolved = true;
    SaveOriginalTransform();

	if (!Component_Interact->CanInteract())
	{
		Component_Widget->SetActive(false);
	}
}

#pragma endregion

#pragma region Restore

void AAnomaly_Object_Base::SaveOriginalTransform()
{
    OriginalTransform = GetActorTransform();
}

void AAnomaly_Object_Base::StartRestoring(float Duration)
{
    GetWorld()->GetTimerManager().ClearTimer(RestoreHandle);

    RestoreDuration = FMath::Max(Duration, 0.01f);
    RestoreCurrentTime = 0.f;

    GetWorld()->GetTimerManager().SetTimer(RestoreHandle, this, &ThisClass::RestoreTick, 0.01f, true);
}

void AAnomaly_Object_Base::RestoreTick()
{
    RestoreCurrentTime += GetWorld()->GetDeltaSeconds();
    float RawAlpha = FMath::Clamp(RestoreCurrentTime / RestoreDuration, 0.f, 1.f);
    float Alpha = FMath::InterpEaseInOut(0.f, 1.f, RawAlpha, 2.f);

    FTransform CurrentTransform = GetActorTransform();
    FTransform NewTransform;
    NewTransform.Blend(CurrentTransform, OriginalTransform, Alpha);
    SetActorTransform(NewTransform);

    if (RawAlpha >= 1.0f)
    {
        FinishRestoring();
    }
}

void AAnomaly_Object_Base::FinishRestoring()
{
    GetWorld()->GetTimerManager().ClearTimer(RestoreHandle);

    SetActorTransform(OriginalTransform);

    if (UPrimitiveComponent* RootPrim = Cast<UPrimitiveComponent>(GetRootComponent()))
    {
        RootPrim->SetSimulatePhysics(false);
    }

    //완료 로직 넣기!
    //bSolved = true;
}

#pragma endregion