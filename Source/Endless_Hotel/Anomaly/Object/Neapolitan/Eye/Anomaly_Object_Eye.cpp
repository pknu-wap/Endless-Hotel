// Copyright by 2026-1 WAP Game 2 team

#include "Anomaly/Object/Neapolitan/Eye/Anomaly_Object_Eye.h"
#include "Player/Character/EHPlayer.h"
#include "GameSystem/SubSystem/FloorProgressSubsystem.h"
#include <Kismet/GameplayStatics.h>
#include <Kismet/KismetMathLibrary.h>
#include <Components/TimelineComponent.h>

#pragma region Base

AAnomaly_Object_Eye::AAnomaly_Object_Eye(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	FloatTimeline = CreateDefaultSubobject<UTimelineComponent>(TEXT("FloatTimeline"));
}

void AAnomaly_Object_Eye::BeginPlay()
{
	Super::BeginPlay();
	auto* FloorSys = GetGameInstance()->GetSubsystem<UFloorProgressSubsystem>();
	FloorSys->FloorChange_Disable.AddUObject(this, &AAnomaly_Object_Eye::DisableObject);
	if (FloatCurve)
	{
		FOnTimelineFloat Update;
		Update.BindUFunction(this, GET_FUNCTION_NAME_CHECKED(ThisClass, OnFloatUpdate));
		FloatTimeline->AddInterpFloat(FloatCurve, Update);

		FOnTimelineEvent Finished;
		Finished.BindUFunction(this, GET_FUNCTION_NAME_CHECKED(ThisClass, OnFloatFinished));
		FloatTimeline->SetTimelineFinishedFunc(Finished);

		FloatTimeline->SetLooping(false);
	}
}

void AAnomaly_Object_Eye::InitializeOnAnomalySpawned()
{
	Super::InitializeOnAnomalySpawned();
	Object->SetVisibility(false);
}

void AAnomaly_Object_Eye::DisableObject()
{
	Object->SetVisibility(false);
	GetWorldTimerManager().ClearTimer(FocusHandle);
	GetWorldTimerManager().ClearTimer(SettleHandle);
	GetWorldTimerManager().ClearTimer(AppearHandle);
}

#pragma endregion

#pragma region EyeAppear

void AAnomaly_Object_Eye::StartEyeAppear()
{
	const float Delay = AppearStartDelay + EyeIndex * AppearInterval;
	GetWorldTimerManager().SetTimer(AppearHandle, this, &ThisClass::ShowEye, Delay, false);
}

void AAnomaly_Object_Eye::ShowEye()
{
	Object->SetVisibility(true);
	StartEyeFocus();
	if (bDropOnAppear)
	{
		StartDrop();
	}
}

void AAnomaly_Object_Eye::StartDrop()
{
	SetActorLocation(GetActorLocation() + DropOffset);
	Object->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	Object->SetEnableGravity(true);
	Object->SetSimulatePhysics(true);
	Object->AddImpulse(GetActorForwardVector() * RollImpulse, NAME_None, true);
	GetWorldTimerManager().SetTimer(SettleHandle, this, &ThisClass::SettleEye, SettleTimeout, false);
}

void AAnomaly_Object_Eye::SettleEye() const
{
	Object->SetSimulatePhysics(false);
	Object->SetEnableGravity(false);
	Object->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	StartEyeFloating();
}

void AAnomaly_Object_Eye::StartEyeFloating() const
{
	FloatTimeline->SetPlayRate(1.f / FloatDuration);
	FloatTimeline->PlayFromStart();
}

void AAnomaly_Object_Eye::OnFloatUpdate(const float Alpha) const
{
	Object->SetWorldLocation(FMath::Lerp(GetActorLocation(), HomeLocation, Alpha));
}

void AAnomaly_Object_Eye::OnFloatFinished()
{
	Object->SetWorldLocation(HomeLocation);
	StartEyeFocus();
}

#pragma endregion

#pragma region EyeFocus

void AAnomaly_Object_Eye::StartEyeFocus()
{
	Object->SetVisibility(true);
	const auto& CachedPlayer = Cast<AEHPlayer>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	CachedPlayer->OnDie.AddUObject(this, &ThisClass::StopEyeFocus);
	GetWorld()->GetTimerManager().SetTimer(FocusHandle, FTimerDelegate::CreateWeakLambda(this, [this, CachedPlayer]()
	{
		const FRotator NewRotation = UKismetMathLibrary::FindLookAtRotation(this->GetActorLocation(), CachedPlayer->GetActorLocation()) + CorrectionRotation;
		this->SetActorRotation(NewRotation);
	}), 0.016f, true);
}

void AAnomaly_Object_Eye::StopEyeFocus(const EDeathReason& DeathReason)
{
	GetWorldTimerManager().ClearTimer(FocusHandle);
}

#pragma endregion