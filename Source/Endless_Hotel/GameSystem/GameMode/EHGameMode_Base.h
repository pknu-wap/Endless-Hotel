// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "EHGameMode_Base.generated.h"

UCLASS()
class ENDLESS_HOTEL_API AEHGameMode_Base : public AGameModeBase
{
	GENERATED_BODY()
	
#pragma region Base

public:
	AEHGameMode_Base(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void BeginPlay() override;

#pragma endregion

};