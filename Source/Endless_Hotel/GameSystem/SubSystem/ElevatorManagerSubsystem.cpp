// Copyright by 2026-1 WAP Game 2 team

#include "GameSystem/SubSystem/ElevatorManagerSubsystem.h"

#include "Actor/Elevator/Elevator.h"

#pragma region Registry

void UElevatorManagerSubsystem::RegisterElevator(AElevator* Elevator)
{
	if (!Elevator)
	{
		return;
	}

	Elevators.Add(Elevator->ElevatorID, Elevator);
}

void UElevatorManagerSubsystem::UnRegisterElevator(FName ElevatorID)
{
	Elevators.Remove(ElevatorID);
}

AElevator* UElevatorManagerSubsystem::GetElevatorByID(FName TargetID)
{
	return Elevators.FindRef(TargetID).Get();
}

#pragma endregion

#pragma region Target Elevator

void UElevatorManagerSubsystem::SetTargetElevator(FName TargetElevatorID)
{
	TargetElevator = Elevators.FindRef(TargetElevatorID);
}

void UElevatorManagerSubsystem::RemoveTargetElevator()
{
	TargetElevator = nullptr;
}

bool UElevatorManagerSubsystem::IsTargetElevator(const AElevator* Elevator) const
{
	return TargetElevator == Elevator;
}

void UElevatorManagerSubsystem::StartAllElevator()
{
	for (const auto& Elevator : Elevators)
	{
		if (Elevator.Value.IsValid())
		{
			Elevator.Value->StartElevator();
		}
	}
}

#pragma endregion

#pragma region Reset

void UElevatorManagerSubsystem::ResetElevatorState()
{
	TargetElevator = nullptr;
	RelativePlayerLocation = FVector::ZeroVector;
	RelativePlayerRotation = FRotator::ZeroRotator;
	ElevatorOffset = FRotator::ZeroRotator;
	PlayerVelocity = 0.f;
}

#pragma endregion