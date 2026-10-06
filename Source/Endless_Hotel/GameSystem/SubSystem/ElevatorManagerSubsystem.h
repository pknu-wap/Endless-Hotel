// Copyright by 2026-1 WAP Game 2 team

#pragma once

#include <CoreMinimal.h>
#include <Subsystems/GameInstanceSubsystem.h>
#include <ElevatorManagerSubsystem.generated.h>

#pragma region Declare

USTRUCT()
struct FElevatorPassengerSnapshot
{
	GENERATED_BODY()

	bool bIsValid = false;
	FVector LocalLocation = FVector::ZeroVector;
	FQuat LocalControlRotation = FQuat::Identity;
	FVector LocalVelocity = FVector::ZeroVector;
	TEnumAsByte<EMovementMode> MovementMode = MOVE_Walking;
};

class AElevator;

#pragma endregion

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
	void StorePassenger(const FElevatorPassengerSnapshot& InSnapshot) { Passenger = InSnapshot; }
	const FElevatorPassengerSnapshot& GetPassenger() const { return Passenger; }

private:
	FElevatorPassengerSnapshot Passenger;

#pragma endregion

#pragma region Reset

public:
	void ResetElevatorState();

#pragma endregion

};