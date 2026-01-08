// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include <CoreMinimal.h>
#include <Subsystems/WorldSubsystem.h>
#include <UHotelWorldSubsystem.generated.h>

UCLASS()
class ENDLESS_HOTEL_API UUHotelWorldSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

protected:
	virtual void OnWorldBeginPlay(UWorld& InWorld) override;

protected:
	UPROPERTY(EditAnywhere)
	FVector PlayerStartLocation = FVector(-1360, 570, 710);
};
