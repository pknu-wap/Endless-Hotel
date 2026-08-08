// Copyright by 2025-2 WAP Game 2 team

#include "GameSystem.h"
#include "Anomaly/Generator/Anomaly_Generator.h"
#include "Asset/Manager/EHAssetManager.h"
#include "GameSystem/GameInstance/EHGameInstance.h"
#include "GameSystem/SaveGame/SaveManager.h"
#include "Anomaly/Event/Anomaly_Event.h"
#include "Anomaly/Object/Anomaly_Object_Base.h"
#include "Anomaly/Event/Neapolitan/Anomaly_Event_Neapolitan.h"
#include "Player/Controller/EHPlayerController.h"
#include "Player/Character/EHPlayer.h"
#include "Actor/Elevator/Elevator.h"
#include <GameFramework/Character.h>
#include <Kismet/GameplayStatics.h>
#include <Engine/World.h>
#include <WorldPartition/WorldPartitionSubsystem.h>

#pragma region Base

UGameSystem::UGameSystem()
{
	GameClearEvent.AddDynamic(this, &ThisClass::GameClear);
}

void UGameSystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	auto& AssetManager = UEHAssetManager::Get();
	AssetManager.InitAnomalyEntries();

	Floor = STARTFLOOR;
	ActIndex = 0;

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

		AssetManager.ResetClearedAnomaly();
		for (const auto& ID : LoadedHistory)
		{
			AssetManager.MarkAnomalyCleared(ID);
		}
	}

	InitializePool();

	ChooseKeyIndex = FMath::RandRange(1, 2);
}

#pragma endregion

#pragma region Level

void UGameSystem::OnChangedDataLayer(const EMapDataLayer& DataLayer)
{
	if (bIsFirstStartFloor)
	{
		bIsStartInBed = true;
		FloorChange_Disable.Broadcast();
	}
	if (VisitedDataLayers.Contains(DataLayer))
	{
		FloorChange_Reset.Broadcast();
	}
	else
	{
		RegisterAnomalyObjectsWhenStreamed(DataLayer);
	}
}

void UGameSystem::RegisterAnomalyObjectsInDataLayer(UWorld* World, const UDataLayerInstance* TargetInstance)
{
	if (!World || !TargetInstance)
	{
		return;
	}

	for (ULevelStreaming* StreamingLevel : World->GetStreamingLevels())
	{
		if (!StreamingLevel)
		{
			continue;
		}
		ULevel* Level = StreamingLevel->GetLoadedLevel();
		if (!Level)
		{
			continue;
		}

		for (AActor* Actor : Level->Actors)
		{
			AAnomaly_Object_Base* AnomalyObject = Cast<AAnomaly_Object_Base>(Actor);
			if (!AnomalyObject)
			{
				continue;
			}

			const TArray<const UDataLayerInstance*> ActorLayers = Actor->GetDataLayerInstancesForLevel();
			if (ActorLayers.Contains(TargetInstance))
			{
				RegisterAnomalyObject(AnomalyObject);
			}
		}
	}
}

void UGameSystem::RegisterAnomalyObjectsWhenStreamed(const EMapDataLayer& DataLayer)
{
	UWorld* World = GetWorld();
	UEHGameInstance* GameInstance = Cast<UEHGameInstance>(GetGameInstance());
	const UDataLayerInstance* TargetInstance = GameInstance ? GameInstance->GetDataLayerInstance(DataLayer) : nullptr;

	if (!World || !TargetInstance)
	{
		return;
	}

	World->GetTimerManager().SetTimer(DataLayerStreamingCheckHandle, FTimerDelegate::CreateWeakLambda(this, [this, World, DataLayer, TargetInstance]()
		{
			UWorldPartitionSubsystem* WPSubsystem = World->GetSubsystem<UWorldPartitionSubsystem>();
			if (!WPSubsystem || !WPSubsystem->IsStreamingCompleted())
			{
				return;
			}
			RegisterAnomalyObjectsInDataLayer(World, TargetInstance);
			VisitedDataLayers.Add(DataLayer);
			World->GetTimerManager().ClearTimer(DataLayerStreamingCheckHandle);
			FloorChange_Reset.Broadcast();
		}), 0.1f, true);
}

#pragma endregion

#pragma region Verdict

bool UGameSystem::ComputeVerdict() const
{
	switch (VerdictMode)
	{
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
	auto& AssetManager = UEHAssetManager::Get();
	bPassed = ComputeVerdict();
	if (bPassed)
	{
		SubFloor();
		bIsStartInBed = false;
		if (bExceptClearedAnomaly)
		{
			AssetManager.MarkAnomalyCleared(CurrentAnomaly->AnomalyID);
			USaveManager::SaveClearedAnomalyID(AssetManager.GetClearedAnomalySet());
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
		if(Cast<AEHPlayer>(Player)->bIsDead)
		{
			bIsStartInBed = true;
			RemoveTargetElevator();
		}
		else
		{
			bIsStartInBed = false;
		}
	}
	bIsAnomalySolved = false;
	bIsFirstStartFloor = false;
	LoadNextMap();
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

void UGameSystem::SetCurrentAnomaly(AAnomaly_Event* Anomaly, EAnomalyID AnomalyID, EMapDataLayer AnomalyMap)
{
	CurrentAnomaly = Anomaly;
	CurrentAnomalyID = AnomalyID;
	CurrentAnomaly->AnomalyID = AnomalyID;
	CurrentDataLayer = AnomalyMap;
	SetTargetElevator();
	CurrentAnomaly->SetAnomalyState();
	if(CurrentAnomaly->AnomalyID != EAnomalyID::Normal)
	{
		++ActIndex;
	}
	StartAllElevator();
}

void UGameSystem::SetNextAnomaly(EAnomalyID AnomalyID, EMapDataLayer AnomalyMap)
{
	NextAnomalyID = AnomalyID;
	NextAnomalyMap = AnomalyMap;
}

void UGameSystem::LoadNextMap()
{
	UEHGameInstance* GameInstance = GetWorld()->GetGameInstance<UEHGameInstance>();
	const EMapDataLayer PrevLayer = CurrentDataLayer;
	GameInstance->SwitchDataLayer(NextAnomalyMap);
	if (PrevLayer == NextAnomalyMap)
	{
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
	auto& AssetManager = UEHAssetManager::Get();
	AnomalyCount = AssetManager.GetOriginAnomaly().Num();
	AssetManager.RebuildActAnomalyFromOrigin();

	ActIndex = 0;

	AssetManager.RemoveNoRuleAnomaly(AnomalyRules);

	if (bExceptClearedAnomaly && !AssetManager.IsClearedAnomalySetEmpty() && AssetManager.GetClearedAnomalyCount() < AnomalyCount)
	{
		AssetManager.RemoveClearedAnomaly();
	}

	AssetManager.ShuffleActAnomaly();

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
	AnomalyObjectPool.FindOrAdd(ActorClass).Objects.AddUnique(Object);
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

void UGameSystem::AddAnomalyRule(const EAnomalyRule& AnomalyRule)
{
	AnomalyRules.AddUnique(AnomalyRule);
	FSaveData_Manual SavedRules;
	SavedRules.ActiveRules = AnomalyRules;
	USaveManager::SaveData_Manual(SavedRules);
	InitializePool();
	OnAddAnomalyRule.Broadcast(AnomalyRule);
}

void UGameSystem::RemoveAnomalyRule(const EAnomalyRule& AnomalyRule)
{
	AnomalyRules.Remove(AnomalyRule);
	FSaveData_Manual SavedRules;
	SavedRules.ActiveRules = AnomalyRules;
	USaveManager::SaveData_Manual(SavedRules);
	InitializePool();
	OnAddAnomalyRule.Broadcast(AnomalyRule);
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

void UGameSystem::StartAllElevator()
{
	for (const auto& Elevator : Elevators)
	{
		Elevator.Value->StartElevator();
	}
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

#pragma region Reset

void UGameSystem::ResetGameSystem()
{
	Floor = STARTFLOOR;
	bIsFirstStartFloor = true;
	bPassed = false;
	bIsAnomalySolved = false;
	bIsElevatorNormal = false;

	AnomalyCount = 0;
	ActIndex = 0;
	CurrentAnomaly = nullptr;
	CurrentAnomalyID = EAnomalyID::None;
	NextAnomalyID = EAnomalyID::None;
	NextAnomalyMap = EMapDataLayer::Hotel;
	CurrentDataLayer = EMapDataLayer::Hotel;
	bIsStartInBed = false;

	TargetElevator = nullptr;
	RelativePlayerLocation = FVector::ZeroVector;
	RelativePlayerRotation = FRotator::ZeroRotator;
	ElevatorOffset = FRotator::ZeroRotator;
	PlayerVelocity = 0.f;

	bIsClear = USaveManager::LoadData_GameClear();
	FSaveData_Setting Data_Setting = USaveManager::LoadData_Setting();
	bExceptClearedAnomaly = Data_Setting.Overlap == EOptionValue::On;
	InitializePool();
}

#pragma endregion