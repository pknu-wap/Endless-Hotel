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

    UFUNCTION()
    void OnObjectDropped(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

protected:
	UPROPERTY(EditAnywhere, Category = "Sound")
    TObjectPtr<class USoundWave> SW_Drop;

private:
    UPROPERTY()
    TWeakObjectPtr<UPrimitiveComponent> TargetMesh;

    UPROPERTY()
    TWeakObjectPtr<class UAudioComponent> Comp_Audio;

#pragma endregion

};