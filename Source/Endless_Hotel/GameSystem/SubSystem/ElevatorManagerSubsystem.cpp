// Copyright by 2026-1 WAP Game 2 team

#include "GameSystem/SubSystem/ElevatorManagerSubsystem.h"
#include "GameSystem/SubSystem/EHGameSystem.h"
#include "Actor/Elevator/Elevator.h"

#pragma region Base

void UElevatorManagerSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	auto* GameSystem = Collection.InitializeDependency<UEHGameSystem>();
	if (GameSystem)
	{
		GameClearHandle = GameSystem->GameClearEvent.AddUObject(this, &UElevatorManagerSubsystem::OnGameClear);
	}
}

#pragma endregion

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
	UE_LOG(LogTemp, Warning, TEXT("[Subsystem] SetTargetElevator %s"), *TargetElevatorID.ToString());
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
	Passenger = FElevatorPassengerSnapshot();
}

#pragma endregion

#pragma region Sound

bool UElevatorManagerSubsystem::GetIsPlayingSound() const
{
	auto* GameSys = GetGameInstance()->GetSubsystem<UEHGameSystem>();
	return GameSys->GetGameProgression() == EGameProgression::CheckIn && bIsPlayingSound;
}

#pragma endregion

#pragma region GameClear

void UElevatorManagerSubsystem::OnGameClear()
{
	SetTargetElevator("LobbyElevator1");
}

#pragma endregion