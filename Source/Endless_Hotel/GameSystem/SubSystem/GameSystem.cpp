// Copyright by 2025-2 WAP Game 2 team

#include "GameSystem.h"
#include "Actor/Anomaly/Anomaly_Generator.h"
#include "GameSystem/GameInstance/EHGameInstance.h"
#include "GameSystem/SaveGame/SaveManager.h"
#include "Data/Anomaly/AnomalyData.h"
#include "Anomaly/Event/Anomaly_Event.h"
#include "Anomaly/Object/Anomaly_Object_Base.h"
#include "Anomaly/Event/Neapolitan/Anomaly_Event_Neapolitan.h"
#include "Data/Controller/DataController.h"
#include "Player/Controller/EHPlayerController.h"
#include "Actor/Elevator/Elevator.h"
#include <GameFramework/Character.h>
#include <Kismet/GameplayStatics.h>

#pragma region Base

UGameSystem::UGameSystem()
{
	GameClearEvent.AddDynamic(this, &ThisClass::GameClear);
}

void UGameSystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	UDataController* DataController = Collection.InitializeDependency<UDataController>();
	if (DataController)
	{
		DataController->GetAnomalyEntries();
	}

	Floor = STARTFLOOR;
	ActIndex = 0;
	AnomalyRules.Add(EAnomalyRule::EightExit);

	bIsClear = USaveManager::LoadData_GameClear();
	FSaveData_Setting Data_Setting = USaveManager::LoadData_Setting();
	FSaveData_Manual Data_Manual = USaveManager::LoadData_Manual();
	bExceptClearedAnomaly = Data_Setting.Overlap == EOptionValue::On ? true : false;

	auto* GameInstance = GetWorld()->GetGameInstance<UEHGameInstance>();
	GameInstance->OnDataLayerChanged.AddDynamic(this, &ThisClass::OnChangedDataLayer);

	AnomalyRules = Data_Manual.ActiveRules;
	if (bIsClear && bExceptClearedAnomaly)
	{
		const TArray<EAnomalyID> LoadedHistory = USaveManager::LoadClearedAnomalyID();
		auto* DataC = GameInstance->GetSubsystem<UDataController>();

		DataC->ClearedAnomalySet.Reset();
		for (const auto& ID : LoadedHistory)
		{
			DataC->ClearedAnomalySet.Add(ID);
		}
	}

	InitializePool();
}
#pragma endregion

#pragma region Level

void UGameSystem::OnChangedDataLayer(const EMapDataLayer& DataLayer)
{
	bIsStartInBed = (bIsStartInBed) ? bIsStartInBed : DataLayer == EMapDataLayer::Lobby;
	for (const auto& Elevator : Elevators)
	{
		Elevator.Value->StartElevator();
	}
}

#pragma endregion

#pragma region Verdict

bool UGameSystem::ComputeVerdict() const
{
	switch (VerdictMode)
	{
	case EAnomalyVerdictMode::SolvedOnly:
		return bIsAnomalySolved;
	case EAnomalyVerdictMode::Both_AND:
		return bIsAnomalySolved && !bIsElevatorNormal;
	case EAnomalyVerdictMode::Normal:
		return bIsAnomalySolved && bIsElevatorNormal;
	default:
		return false;
	}
}

void UGameSystem::ApplyVerdict()
{
	auto* DataC = GetGameInstance()->GetSubsystem<UDataController>();
	bPassed = ComputeVerdict();
	if (bPassed)
	{
		SubFloor();

		if (bExceptClearedAnomaly)
		{
			DataC->ClearedAnomalySet.Add(CurrentAnomaly->AnomalyName);
			USaveManager::SaveClearedAnomalyID(DataC->ClearedAnomalySet.Array());
		}
	}
	else 
	{ 
		ACharacter* Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
		AEHPlayerController* PC = Cast<AEHPlayerController>(Player->GetController());
		PC->SetPlayerInputAble(true);
		ResetFloor();

		UEHGameInstance* GameInstance = GetWorld()->GetGameInstance<UEHGameInstance>();
		NextAnomalyMap = EMapDataLayer::Hotel;
	}
	bIsAnomalySolved = false;
}

void UGameSystem::TryInteractSolveVerdict()
{
	if (AAnomaly_Event* Neo = Cast<AAnomaly_Event>(CurrentAnomaly))
	{
		Neo->InteractSolveVerdict();
	}
}

#pragma endregion

#pragma region Anomaly

void UGameSystem::SetCurrentAnomaly(AAnomaly_Event* Anomaly, EAnomalyID AnomalyName, EMapDataLayer AnomalyMap)
{
	CurrentAnomaly = Anomaly;
	CurrentAnomaly->AnomalyName = AnomalyName;
	CurrentDataLayer = AnomalyMap;
	SetTargetElevator();
	CurrentAnomaly->SetAnomalyState();
	ActIndex++;
}

void UGameSystem::SetNextAnomaly(EAnomalyID AnomalyName, EMapDataLayer AnomalyMap)
{
	NextAnomalyID = AnomalyName;
	NextAnomalyMap = AnomalyMap;
}

void UGameSystem::LoadNextMap()
{
	UEHGameInstance* GameInstance = GetWorld()->GetGameInstance<UEHGameInstance>();
	GameInstance->SwitchDataLayer(NextAnomalyMap);
	if (!bIsClear)
	{
		FloorChange_Disable.Broadcast();
		FloorChange_Reset.Broadcast();
	}
}

#pragma endregion

#pragma region Floor

void UGameSystem::SubFloor()
{
	if (Floor > 1)
	{
		Floor--;
	}
	else
	{
		GameClearEvent.Broadcast();
	}
}

void UGameSystem::AddFloor()
{
	if (Floor < 8)
	{
		Floor++;
	}
}

#pragma endregion

#pragma region Pool & Reset

void UGameSystem::InitializePool()
{
	// Copy from Original
	auto* DataC = GetGameInstance()->GetSubsystem<UDataController>();
	AnomalyCount = DataC->GetOriginAnomaly().Num();
	DataC->ActAnomaly.Empty();
	DataC->ActAnomaly.Append(DataC->GetOriginAnomaly());

	ActIndex = 0;

	// Temp Logic : Remove Anomaly By Rule
	// DataC->RemoveNoRuleAnomaly();

	if (bExceptClearedAnomaly && !DataC->ClearedAnomalySet.IsEmpty() && DataC->ClearedAnomalySet.Num() < AnomalyCount)
	{
		DataC->RemoveClearedAnomaly();
	}

	// Shuffle
	if (DataC->ActAnomaly.Num() > 1)
	{
		for (uint8 CurrentIndex = DataC->ActAnomaly.Num() - 1; CurrentIndex > 0; --CurrentIndex)
		{
			const uint8 RandomIndex = FMath::RandRange(0, CurrentIndex);
			if (CurrentIndex != RandomIndex)
			{
				DataC->ActAnomaly.Swap(CurrentIndex, RandomIndex);
			}
		}
	}

	// Reset Index
	ActIndex = 0;
}

void UGameSystem::RegisterAnomalyObject(AAnomaly_Object_Base* Object)
{
	if (!IsValid(Object))
	{
		return;
	}
	UClass* ActorClass = Object->GetClass();
	AnomalyObjectPool.FindOrAdd(ActorClass).Objects.Add(Object);
}

void UGameSystem::UnRegisterAnomalyObject(AAnomaly_Object_Base* Object)
{
	if (!Object) return;
	UClass* TargetClass = Object->GetClass();
	if (FAnomalyObjectArray* FoundStruct = AnomalyObjectPool.Find(TargetClass))
	{
		FoundStruct->Objects.Remove(Object);
		if (FoundStruct->Objects.IsEmpty())
		{
			AnomalyObjectPool.Remove(TargetClass);
		}
		if(IsValid(CurrentAnomaly))
		{
			CurrentAnomaly->LinkedObjects.Remove(Object);
		}
	}
}

#pragma endregion

#pragma region Clear

void UGameSystem::GameClear()
{
	bIsClear = true;
	Floor = STARTFLOOR;

	USaveManager::SaveData_GameClear(true);
}

void UGameSystem::RegisterElevator(class AElevator* Elevator)
{
	Elevators.Add(Elevator->ElevatorID, Elevator);
}

void UGameSystem::UnRegisterElevator(FName ElevatorID)
{
	Elevators.Remove(ElevatorID);
}

void UGameSystem::SetTargetElevator()
{
	TargetElevator = Elevators.FindRef(CurrentAnomaly->TargetElevatorID);
}

void UGameSystem::RemoveTargetElevator()
{
	TargetElevator = nullptr;
}

AElevator* UGameSystem::GetElevatorByID(FName TargetID)
{
	return Elevators.FindRef(TargetID).Get();
}

bool UGameSystem::IsTargetElevator(const AElevator* Elevator)
{
	return (TargetElevator == Elevator) ? true : false;
}

#pragma endregion