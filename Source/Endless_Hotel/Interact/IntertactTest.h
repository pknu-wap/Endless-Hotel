// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "CoreMinimal.h"
#include "Actor/EHActor.h"
#include "Interact/InteractableObject.h"
#include "IntertactTest.generated.h"

UCLASS()
class ENDLESS_HOTEL_API AInteractTest : public AEHActor, public IInteractableObject
{
    GENERATED_BODY()

#pragma region Base

public:
    AInteractTest(const FObjectInitializer& ObjectInitializer);

protected:
    virtual void BeginPlay() override;

protected:
    UPROPERTY(EditAnywhere)
    TObjectPtr<class UStaticMeshComponent> CubeMesh;

#pragma endregion

// 해당 region 내의 요소들은 반드시 구현해야 함
#pragma region Interact

public:
    virtual void Interacted_Implementation() override;
    virtual void ShowInteractWidget_Implementation(bool bIsShow) override;

protected:
    UPROPERTY(EditAnywhere)
    TObjectPtr<class UWidgetComponent> WC;

    UPROPERTY()
    TObjectPtr<class UUI_Interact> UI_Interact;

    UPROPERTY()
    TObjectPtr<class ULookAtComponent> LAC;

#pragma endregion

};