// Copyright by 2025-2 WAP Game 2 team

#include "GameSystem.h"
#include "GameSystem/Anomaly/Anomaly_Generator.h"
#include "GameSystem/GameInstance/EHGameInstance.h"
#include "GameSystem/SaveGame/SaveManager.h"
#include "Data/Anomaly/AnomalyData.h"
#include "Anomaly/Base/Anomaly_Event.h"
#include "Anomaly/Object/Anomaly_Object_Base.h"
#include "Anomaly/Base/Anomaly_Event_Neapolitan.h"
#include "Data/Controller/DataController.h"

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

	Floor = 9;
	AnomalyCount = 0;
	ActIndex = 0;

	bIsAlreadyClear = USaveManager::LoadGameClearData();
	if (bIsAlreadyClear)
	{
		const TArray<uint8> LoadedHistory = USaveManager::LoadClearedAnomalyID();
		auto* DataC = GetGameInstance()->GetSubsystem<UDataController>();

		DataC->LoadedAnomalySet.Reset();
		for (uint8 ID : LoadedHistory)
		{
			DataC->LoadedAnomalySet.Add(ID);
		}
	}

	InitializePool();
}
#pragma endregion

#pragma region Verdict

bool UGameSystem::ComputeVerdict(bool bSolved, bool bNormalElevator) const
{
	switch (VerdictMode)
	{
	case EAnomalyVerdictMode::SolvedOnly:
		return bSolved;
	case EAnomalyVerdictMode::Both_AND:
		return bSolved && !bNormalElevator;
	case EAnomalyVerdictMode::Normal:
		return bSolved && bNormalElevator;
	default:
		return false;
	}
}

void UGameSystem::ApplyVerdict()
{
	auto* DataC = GetGameInstance()->GetSubsystem<UDataController>();
	bPassed = ComputeVerdict(bIsAnomalySolved, bIsElevatorNormal);
	if (bPassed)
	{
		SubFloor();
		if(!AnomalyHistory.Contains(CurrentAnomalyID))
		{
			AnomalyHistory.Add(CurrentAnomalyID);
		}
		if (bIsAlreadyClear)
		{
			DataC->LoadedAnomalySet.Add(CurrentAnomalyID);
			USaveManager::SaveClearedAnomalyID(CurrentAnomalyID);
		}
		AnomalyCount++;
	}
	else 
	{ 
		ResetFloor();
	}
	bIsAnomalySolved = false;

	if (!bIsClear)
	{
		UEHGameInstance* GameInstance = GetWorld()->GetGameInstance<UEHGameInstance>();
		GameInstance->OpenLevel(ELevelType::Hotel, false);
	}
}

void UGameSystem::TryInteractSolveVerdict()
{
	if (AAnomaly_Event* Neo = Cast<AAnomaly_Event>(CurrentAnomaly))
	{
		Neo->InteractSolveVerdict();
	}
}

#pragma endregion

#pragma region Floor

void UGameSystem::SubFloor()
{
	if (Floor > 2)
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
	
	DataC->ActAnomaly = DataC->GetOriginAnomaly();

	ActIndex = 0;

	if (bIsAlreadyClear && DataC->LoadedAnomalySet.Num() > 0)
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

#pragma endregion

#pragma region Clear

void UGameSystem::GameClear()
{
	// USaveManager에 로드 세이브 데이터로 클리어 여부 가져올 수 있음
	bIsClear = true;		// 게임 최초 클리어인지 판단용 bool 변수 -> 진행상황 리셋 추가 시 해당 변수 사용 예정
	//Initialize();
	//Todo:

	Floor = 9;

	USaveManager::SaveGameClearData();
}

#pragma endregion
