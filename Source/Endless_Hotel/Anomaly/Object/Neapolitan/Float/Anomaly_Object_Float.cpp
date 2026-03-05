// Copyright by 2025-2 WAP Game 2 team

#include "Anomaly/Object/Neapolitan/Float/Anomaly_Object_Float.h"
#include "Anomaly/Object/Neapolitan/Anomaly_Object_Neapolitan.h"
#include "Components/WidgetComponent.h"   
#include "Component/Float/FloatComponent.h"
#include "Component/Interact/InteractComponent.h"
#include <EngineUtils.h>

#pragma region Base

#define LOCTEXT_NAMESPACE "Float"

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
    bSolved = false;

    for (TActorIterator<AActor> It(GetWorld()); It; ++It)
    {
        AActor* Target = *It;

        auto* FloatComp = Target->FindComponentByClass<UFloatComponent>();

        if (FloatComp)
        {
            AffectedActors.Add(Target);
            FloatComp->StartFloating();
            FloatComp->OnRestored.AddDynamic(this, &ThisClass::OnActorRestored);
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