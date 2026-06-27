// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "Component/EHComponent.h"
#include <CoreMinimal.h>
#include <FloatComponent.generated.h>

UCLASS(meta = (BlueprintSpawnableComponent))
class ENDLESS_HOTEL_API UFloatComponent : public UEHComponent
{
    GENERATED_BODY()

#pragma region Base

protected:
    virtual void BeginPlay() override;

#pragma endregion

#pragma region Float

public:
    void StartFloating();
    
private:
    void StopFloating();
    void DropObject();

private:
    UPROPERTY()
    TWeakObjectPtr<UPrimitiveComponent> TargetMesh;

#pragma endregion

};