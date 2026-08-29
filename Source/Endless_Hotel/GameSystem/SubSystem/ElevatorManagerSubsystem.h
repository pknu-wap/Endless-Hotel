// Copyright by 2026-1 WAP Game 2 team

#pragma once

#include <CoreMinimal.h>
#include <Subsystems/GameInstanceSubsystem.h>
#include <ElevatorManagerSubsystem.generated.h>

class AElevator;

UCLASS()
class ENDLESS_HOTEL_API UElevatorManagerSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

#pragma region Registry

public:
	void RegisterElevator(AElevator* Elevator);
	void UnRegisterElevator(FName ElevatorID);

	AElevator* GetElevatorByID(FName TargetID);

private:
	TMap<FName, TWeakObjectPtr<AElevator>> Elevators;

#pragma endregion

#pragma region Target Elevator

public:
	void SetTargetElevator(FName TargetElevatorID);
	void RemoveTargetElevator();
	bool IsTargetElevator(const AElevator* Elevator) const;

	void StartAllElevator();

private:
	TWeakObjectPtr<AElevator> TargetElevator = nullptr;

#pragma endregion

#pragma region Player In Elevator

public:
	void SetPlayerinElevatorTransform(const FVector& PlayerLocation, const FRotator& PlayerRotation, const FRotator& Offset)
	{
		RelativePlayerLocation = PlayerLocation;
		RelativePlayerRotation = PlayerRotation;
		ElevatorOffset = Offset;
	}
	void SetPlayerVelocity(float InputHorizontalVelocity) { PlayerVelocity = InputHorizontalVelocity; }

	float GetPlayerVelocity() const { return PlayerVelocity; }
	FVector GetPlayerinElevatorLocation() const { return RelativePlayerLocation; }
	FRotator GetPlayerinElevatorRotation() const { return RelativePlayerRotation; }
	FRotator GetElevatorOffset() const { return ElevatorOffset; }

private:
	FVector RelativePlayerLocation = FVector::ZeroVector;
	FRotator RelativePlayerRotation = FRotator::ZeroRotator;
	FRotator ElevatorOffset = FRotator::ZeroRotator;
	float PlayerVelocity = 0.f;

#pragma endregion

#pragma region Reset

public:
	void ResetElevatorState();

#pragma endregion
};