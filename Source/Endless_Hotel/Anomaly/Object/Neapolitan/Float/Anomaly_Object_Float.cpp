// Copyright by 2025-2 WAP Game 2 team

#include "Anomaly/Object/Neapolitan/Float/Anomaly_Object_Float.h"
#include "Anomaly/Object/Neapolitan/Anomaly_Object_Neapolitan.h"
#include "Components/WidgetComponent.h"   
#include "Component/Float/FloatComponent.h"
#include "Component/Interact/InteractComponent.h"
#include <EngineUtils.h>

#pragma region Base

#define LOCTEXT_NAMESPACE "Float"

AAnomaly_Object_Float::AAnomaly_Object_Float(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    bIsFloating = false;
    bSolved = false;   
}

void AAnomaly_Object_Float::BeginPlay()
{
    Super::BeginPlay();

    AffectedActors.Empty();
    RestoredActors.Empty();
}

#pragma endregion

#pragma region Floating

void AAnomaly_Object_Float::SearchAndStart()
{
    for (TActorIterator<AActor> It(GetWorld()); It; ++It)
    {
        AActor* Target = *It;

        auto* InteractComp = Target->FindComponentByClass<UInteractComponent>();
        auto* FloatComp = Target->FindComponentByClass<UFloatComponent>();

        if (InteractComp && FloatComp)
        {
            AffectedActors.Add(Target);
            FloatComp->StartFloating();

            InteractComp->OnRestored.AddDynamic(this, &AAnomaly_Object_Float::OnActorRestored);
        }
    }
}

// 복구될 때마다 호출되는 콜백 함수
void AAnomaly_Object_Float::OnActorRestored(AActor* RestoredActor)
{
    if (RestoredActors.Contains(RestoredActor)) return;

    RestoredActors.Add(RestoredActor);

    // 전체 검사
    if (RestoredActors.Num() >= AffectedActors.Num())
    {
        CheckAllRestored();
    }
}

void AAnomaly_Object_Float::StartFloating()
{
    bIsFloating = true;

    Object->SetSimulatePhysics(false);
    Object->SetEnableGravity(false);
    Object->SetPhysicsLinearVelocity(FVector::ZeroVector);

    FloatVelocity = FVector(
        FMath::RandRange(-10.f, 10.f),
        FMath::RandRange(-10.f, 10.f),
        FMath::RandRange(20.f, 40.f)
    );

    RotationVelocity = FRotator(
        FMath::RandRange(-30.f, 30.f),
        FMath::RandRange(-30.f, 30.f),
        FMath::RandRange(-30.f, 30.f)
    );

    GetWorld()->GetTimerManager().SetTimer(FloatTickTimer, FTimerDelegate::CreateWeakLambda(this, [this]()
        {
            FloatAccelerate();
        }), 0.016f, true);

    GetWorld()->GetTimerManager().SetTimer(StopFloatTimer, FTimerDelegate::CreateWeakLambda(this, [this]()
        {
            StopFloating();
        }), 10, false);
}

void AAnomaly_Object_Float::FloatAccelerate()
{
    if (!bIsFloating) return;

    const float DeltaTime = GetWorld()->GetDeltaSeconds();

    AddActorWorldOffset(FloatVelocity * DeltaTime, true);
    AddActorWorldRotation(RotationVelocity * DeltaTime);
}

void AAnomaly_Object_Float::StopFloating()
{
    if (!bIsFloating) return;

    bIsFloating = false;

    GetWorldTimerManager().ClearTimer(FloatTickTimer);
    GetWorldTimerManager().ClearTimer(StopFloatTimer);

    Object->SetSimulatePhysics(true);
    Object->SetEnableGravity(true);
}

#pragma endregion

#pragma region Restore

#pragma endregion

#pragma region Interact

void AAnomaly_Object_Float::CheckAllRestored()
{
    if (AffectedActors.Num() > 0 && RestoredActors.Num() >= AffectedActors.Num())
    {
        bSolved = true;

        // 디버그 로그 (확인용)
        UE_LOG(LogTemp, Warning, TEXT("Anomaly Float Solved! All objects restored."));
    }
}
#pragma endregion
