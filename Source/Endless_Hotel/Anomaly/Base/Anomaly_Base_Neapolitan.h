// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include <Anomaly/Base/Anomaly_Base.h>
#include <CoreMinimal.h>
#include <Anomaly_Base_Neapolitan.generated.h>

// Anomaly_Base_Neapolitan.h
UCLASS()
class ENDLESS_HOTEL_API AAnomaly_Base_Neapolitan : public AAnomaly_Base
{
    GENERATED_BODY()
#pragma region Base

public:
    AAnomaly_Base_Neapolitan(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

protected:
    virtual void BeginPlay() override;

#pragma endregion

#pragma region Activities

public:
    virtual void InteractSolveVerdict();   //상호작용 이상현상 판정
protected:
    virtual void ActivateAnomaly() override;
    
#pragma endregion

};
