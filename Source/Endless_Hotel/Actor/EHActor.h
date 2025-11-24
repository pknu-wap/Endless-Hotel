// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EHActor.generated.h"

UCLASS()
class ENDLESS_HOTEL_API AEHActor : public AActor
{
	GENERATED_BODY()
	
#pragma region Base

public:
	AEHActor(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void EndPlay(EEndPlayReason::Type EndPlayReason) override;

#pragma endregion

};