// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include <CoreMinimal.h>
#include <GameFramework/Character.h>
#include <EHCharacter.generated.h>

UCLASS()
class ENDLESS_HOTEL_API AEHCharacter : public ACharacter
{
	GENERATED_BODY()

#pragma region Base

public:
	AEHCharacter(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void EndPlay(EEndPlayReason::Type EndPlayReason) override;

#pragma endregion

};