// Copyright by 2025-2 WAP Game 2 team


#include "Anomaly/Base/Anomaly_Base_Neapolitan.h"
#include "GameSystem/SubSystem/AnomalyProgressSubSystem.h"
#include "Anomaly/Object/Anomaly_Object_Base.h"

// Anomaly_Base_Neapolitan.cpp

AAnomaly_Base_Neapolitan::AAnomaly_Base_Neapolitan(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
}

void AAnomaly_Base_Neapolitan::BeginPlay()
{
	Super::BeginPlay();
	SetVerdictMode(EAnomalyVerdictMode::Both_AND); // VerdictMode Setting
}

void AAnomaly_Base_Neapolitan::ActivateAnomaly(uint8 Anomaly_ID)
{
    // Activites
    UE_LOG(LogTemp, Log, TEXT("[Neapolitan] Activated."));
}

void AAnomaly_Base_Neapolitan::InteractSolveVerdict()
{
    //상호작용 기반 해결여부
    UAnomalyProgressSubSystem* Sub = GetGameInstance()->GetSubsystem<UAnomalyProgressSubSystem>();
    bool bAllSolved = true;
    for (auto* FoundActor : LinkedObjects)
    {
        auto* AnomalyObject = Cast<AAnomaly_Object_Base>(FoundActor);
        /*if (!AnomalyObject->bSolved)
        {
            bAllSolved = false;
            break;
        }*/
    }
    bIsSolved = bAllSolved;
    Sub->SetIsAnomalySolved(bIsSolved);
}
