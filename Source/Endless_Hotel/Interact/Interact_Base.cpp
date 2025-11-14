// Copyright by 2025-2 WAP Game 2 team

#include "Interact/Interact_Base.h"
#include "GameFramework/PlayerController.h"

#pragma region Base

AInteract_Base::AInteract_Base(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = false;
}

void AInteract_Base::Interact_Implementation(APlayerController* InteractingController)
{
    if (InteractingController)
    {
        UE_LOG(LogTemp, Log, TEXT("%s가 상호작용을 시도했습니다."), *InteractingController->GetName());
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Interact 호출자 없음"));
    }
}

#pragma endregion