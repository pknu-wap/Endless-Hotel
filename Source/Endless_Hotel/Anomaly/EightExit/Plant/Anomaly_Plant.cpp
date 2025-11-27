// Copyright by 2025-2 WAP Game 2 team


#include "Anomaly/EightExit/Plant/Anomaly_Plant.h"
#include "Anomaly/Object/Plant/Anomaly_Object_Plant.h"
#include "Kismet/GameplayStatics.h"

#pragma region Activity

void AAnomaly_Plant::ActivateAnomaly_Implementation(uint8 Anomaly_ID)
{
    Super::ActivateAnomaly_Implementation(Anomaly_ID);

    switch (Anomaly_ID)
    {
    case 10:
        AnomalyAction = ([](AAnomaly_Object_Base* AnomalyObject)
        {
            if (auto* Plant = Cast<AAnomaly_Object_Plant>(AnomalyObject))
            {
                Plant->ChangeToAfterState();
            }
        });
        break;
    }
}

#pragma endregion

#pragma region AutoLink

void AAnomaly_Plant::BeginPlay()
{
    Super::BeginPlay();

    TArray<AActor*> FoundPlants;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), AAnomaly_Object_Plant::StaticClass(), FoundPlants);

    LinkedObjects = FoundPlants;

    UE_LOG(LogTemp, Warning, TEXT("Anomaly_Plant: Linked %d plant objects."), FoundPlants.Num());
}

#pragma endregion