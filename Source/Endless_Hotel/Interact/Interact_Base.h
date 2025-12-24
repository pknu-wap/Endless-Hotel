// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "CoreMinimal.h"
#include "Anomaly/Object/Anomaly_Object_Base.h"
#include "Interact_Base.generated.h"

UCLASS()
class ENDLESS_HOTEL_API AInteract_Base : public AAnomaly_Object_Base
{
    GENERATED_BODY()

#pragma region Base

public:
    AInteract_Base(const FObjectInitializer& ObjectInitializer);

#pragma endregion

#pragma region Interact

public:
    virtual void Interacted();

#pragma endregion

#pragma region Neapolitan
public:
    bool bSolved;
#pragma endregion
};